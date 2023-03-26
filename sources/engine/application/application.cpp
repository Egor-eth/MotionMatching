#include "application_data.h"
#include "application.h"
#include "render/shader/shader_factory.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "profiler/profiler.h"
#include <SDL2/SDL.h>
#include "template.h"
#include "ecs/ecs_scene.h"
#include "application_metainfo.h"
#include "memory/tmp_allocator.h"
#include <mutex>

namespace ecs
{
  void load_templates_from_blk();
}
void create_all_resources_from_metadata();
void save_all_resources_to_metadata();

static std::mutex jobsMutex;

Application::Application(const std::string &project_name,const std::string &root, int width, int height, bool full_screen):
context(project_name, width, height, full_screen), timer(), scene(new ecs::SceneManager()),
root(root),
projectPath(root + "/" + project_name)
{
  assert(scene);
  application = this;
}

static void copy_paths(const std::string &root, const ecs::vector<ecs::string> &src, std::vector<std::filesystem::path> &dst)
{
  dst.resize(src.size());
  for (int i = 0, n = src.size(); i < n; i++)
    dst[i] = std::filesystem::path(root + "/" + src[i].c_str());
}

void Application::start()
{
  ApplicationMetaInfo metaInfo(projectPath + "/project.config");
  copy_paths(root, metaInfo.shadersPaths, shadersPaths);
  copy_paths(root, metaInfo.resourcesPaths, resourcesPaths);
  copy_paths(root, metaInfo.templatePaths, templatePaths);
  compile_shaders();
    context.start_imgui();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  bool editor = !metaInfo.startGame;
  
  #ifdef RELEASE
  editor = false;
  #endif
  scene->start();
  create_all_resources_from_metadata();
  ecs::load_templates_from_blk();
  get_cpu_profiler();
  get_gpu_profiler();

  scene->start_scene(root_path(metaInfo.firstScene.c_str()), editor);
}
bool Application::sdl_event_handler()
{
  SDL_Event event;
  bool running = true;
  Input &input = Input::input();
  while (SDL_PollEvent(&event))
  {
    ImGui_ImplSDL2_ProcessEvent(&event);
    switch(event.type){
      case SDL_QUIT: running = false; break;
      
      case SDL_KEYDOWN: 
      
      if(event.key.keysym.sym == SDLK_F2)
        scene->restart_cur_scene();
      
      if(event.key.keysym.sym == SDLK_F3)
        scene->swap_editor_game_scene();
      
      case SDL_KEYUP: input.event_process(event.key, Time::time());

      if(event.key.keysym.sym == SDLK_ESCAPE)
        running = false;
        

      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP: input.event_process(event.button, Time::time()); break;

      case SDL_MOUSEMOTION: input.event_process(event.motion, Time::time()); break;

      case SDL_MOUSEWHEEL: input.event_process(event.wheel, Time::time()); break;
      
      case SDL_WINDOWEVENT: break;
    }
  }
  return running;
}
void Application::main_loop()
{
  bool running = true;
  while (running)
  {
    clear_tmp_allocation();
    get_cpu_profiler().start_frame();
    PROFILER(main_loop);
    timer.update();

    std::unique_lock<std::mutex> lock(jobsMutex);
    auto jobs = std::move(mainThreadJobs);
    mainThreadJobs.clear();
    lock.unlock();
    for(auto &job: jobs) {
      job();
    }
    /*
      for (uint i = 0; i < mainThreadJobsCount; i++)
        mainThreadJobs[i]();
      mainThreadJobs.erase(mainThreadJobs.begin(), mainThreadJobs.begin() + mainThreadJobsCount);
*/
    PROFILER(sdl_events) 
		running = sdl_event_handler();
    sdl_events.stop();
    if (running)
    {
      PROFILER(ecs_events);
      scene->process_events();
      ecs_events.stop();
      PROFILER(ecs_act);
      scene->update_act();
      ecs_act.stop();
      
      PROFILER(swapchain);
      context.swap_buffer();
      swapchain.stop();
      extern void process_gpu_time_queries();
      process_gpu_time_queries();
      get_gpu_profiler().start_frame();
      ProfilerLabelGPU frame_label("frame");
      PROFILER(ecs_render);
      scene->update_render();
      ecs_render.stop();
      
      PROFILER(ui)
      context.start_imgui();
      PROFILER(ecs_ui);
      scene->update_ui();
      ecs_ui.stop();
      
      ProfilerLabelGPU imgui_render_label("imgui_render");
      PROFILER(imgui_render);
      ImGui::Render();
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
      imgui_render.stop();
      ui.stop();
    }
    main_loop.stop();
	}
}
void Application::exit()
{
  save_shader_info();
  scene->destroy_scene();
  save_all_resources_to_metadata();
  delete scene;
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();
  SDL_Quit();
}
std::string project_path(const std::string &path)
{
  return Application::instance().projectPath + "/" + path;
}
std::string project_path()
{
  return Application::instance().projectPath;
}
std::string root_path(const std::string &path)
{
  return Application::instance().root + "/" + path;
}
std::string root_path()
{
  return Application::instance().root;
}

void add_main_thread_job(std::function<void()> &&job)
{
  std::unique_lock<std::mutex> lock(jobsMutex);
  Application::instance().mainThreadJobs.emplace_back(std::move(job));
}

std::pair<int,int> get_resolution()
{
  Resolution r = Application::get_context().get_resolution();
  return {r.width, r.height};
}

void create_scene(const char *path)
{
  Application::instance().scene->sceneToLoad = path;
}