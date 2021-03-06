/*
 * Authors: M. Kristien
 * Organisation: HYPED
 * Date: 2. April 2018
 * Description:
 *
 *    Copyright 2018 HYPED
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#ifndef BEAGLEBONE_BLACK_UTILS_SYSTEM_HPP_
#define BEAGLEBONE_BLACK_UTILS_SYSTEM_HPP_

#include <cstdint>

#include "concurrent/barrier.hpp"
#include "logger.hpp"
#include "utils.hpp"

namespace hyped {

using utils::concurrent::Barrier;

namespace utils {

class System {
 public:
  static void parseArgs(int argc, char* argv[]);
  static System& getSystem();
  static Logger& getLogger();

  /**
   * Register custom signal handler for CTRL+C to make system exit gracefully
   */
  static void setExitFunction();

  // runtime arguments to configure the whole system
  int8_t verbose;
  int8_t verbose_motor;
  int8_t verbose_nav;
  int8_t verbose_sensor;
  int8_t verbose_state;
  int8_t verbose_cmn;

  int8_t debug;
  int8_t debug_motor;
  int8_t debug_nav;
  int8_t debug_sensor;
  int8_t debug_state;
  int8_t debug_cmn;

  bool fake_imu;

  // barriers
  /**
   * @brief Barrier used by navigation and motor control modules on stm transition to accelerating
   *        state. Navigation must finish calibration before motors start spinning.
   */
  Barrier navigation_motors_sync_ = Barrier(2);

 private:
  Logger* log_;
  System() = delete;
  System(int argc, char* argv[]);
  ~System();
  static System* system_;

  // macro to help implemet singleton
  NO_COPY_ASSIGN(System);
};

}}  // namespace hyped::utils

#endif  // BEAGLEBONE_BLACK_UTILS_SYSTEM_HPP_
