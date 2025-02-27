#pragma once
#include "application/time.h"
#include <vector>
#include <map>
class ProfilerLabel
{
private:
  uint64_t start; 
  const char *label;
  bool stopped;
public:
  ProfilerLabel(const char *label);
  ~ProfilerLabel();
  void stop();
};
class ProfilerLabelGPU
{
private:
  bool stopped;
  uint startQuery, endQuery;
  const char *label;
public:
  ProfilerLabelGPU(const char *label);
  ~ProfilerLabelGPU();
  void stop();
};

struct TimeLabel {int id; const char *label; bool open;};
class Profiler
{
private:
  struct AverangeTime 
  {
      std::vector<float> dtChain;
    int curIndex;
    float curSum;
    AverangeTime();
    float get_averange() const;
    float get_max() const;
    void add_time(float dt);
  };

  std::map<uint64_t, AverangeTime> labelAveranges;
  std::map<uint64_t, int> labelCount;
  std::vector<TimeLabel> prev_frame_labels, cur_frame_labels;
public:
  void start_frame();
  void open_label(const char *label);
  void close_label(float time_ms, const char *label);
  float get_averange(const TimeLabel &label);
  float get_max(const TimeLabel &label);
  const std::vector<TimeLabel> &get_frame_history();
};

Profiler &get_cpu_profiler();
Profiler &get_gpu_profiler();
#define PROFILER(label) ProfilerLabel label(#label);