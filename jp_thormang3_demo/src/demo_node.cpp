/*******************************************************************************
* Copyright 2019 ROBOTIS Japan CO., LTD.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Author: Yoshimaru Tanaka */

#include <ros/ros.h>
#include <std_msgs/String.h>

void playSound(const std::string &path);
void demoModeCommandCallback(const std_msgs::String::ConstPtr &msg);

const int SPIN_RATE = 30;
ros::Publisher play_sound_pub;
std::string default_mp3_path = "";

int main(int argc, char **argv)
{
  //init ros
  ros::init(argc, argv, "demo_node");
  ros::NodeHandle nh(ros::this_node::getName());

  ros::Subscriber sound_command_sub = nh.subscribe("/robotis/mode_command", 1, demoModeCommandCallback);
  default_mp3_path = ros::package::getPath("jp_thormang3_demo") + "/data/mp3/";
  play_sound_pub = nh.advertise<std_msgs::String>("/play_sound_file", 0);

  // ros::start();
  ros::Rate loop_rate(SPIN_RATE);

  //node loop
  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}

void playSound(const std::string &path)
{
  std_msgs::String sound_msg;
  sound_msg.data = path;

  play_sound_pub.publish(sound_msg);
}

void demoModeCommandCallback(const std_msgs::String::ConstPtr &msg)
{
  if (msg->data == "ready")
    {
      playSound(default_mp3_path + "Demonstration ready mode.mp3");
    }
  else if(msg->data == "soccer")
    {
      // play sound
      playSound(default_mp3_path + "Start soccer demonstration.mp3");
    }
  else if(msg->data == "vision")
    {
      // play sound
      playSound(default_mp3_path + "Start vision processing demonstration.mp3");
    }
  else if(msg->data == "action")
    {
      // play sound
      playSound(default_mp3_path + "Start motion demonstration.mp3");
    }
}

