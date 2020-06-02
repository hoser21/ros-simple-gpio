# ros_simple_gpio

## Requirements
- Ubuntu 18.04 arm64 raspi
- ROS Melodic
- pigpio

## Raspberry Pi Setup

Install GNU C compiler and GNU C++ compiler

```sudo apt install build-essential```

Install pigpio. See [here](http://abyz.me.uk/rpi/pigpio/download.html) for more information.

```
cd /tmp

wget https://github.com/joan2937/pigpio/archive/master.zip

unzip master.zip

cd pigpio-master

make

sudo make install
```

## ROS Melodic Installation with Python 3 Support

ROS melodic's prebuilt packages uses Python 2 packages, so we need to compile ROS from source to have it use Python 3. See http://wiki.ros.org/melodic/Installation/Source for more information.

```
sudo apt-get install python3-rosdep python3-rosinstall-generator python3-wstool python3-rosinstall build-essential

sudo rosdep init

rosdep update

mkdir ~/ros_catkin_ws

cd ~/ros_catkin_ws

rosinstall_generator ros_comm --rosdistro melodic --deps --tar > melodic-ros_comm.rosinstall

wstool init -j8 src melodic-ros_comm.rosinstall

export ROS_PYTHON_VERSION=3

rosdep install --from-paths src --ignore-src --rosdistro melodic -y

./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release

echo "source ~/ros_catkin_ws/install_isolated/setup.bash
" >> ~/.bashrc

source ~/.bashrc
```

## Usage

The listener node toggles LEDs on GPIO pins 4 and 17 (BCM).

```sudo pigpiod```

Run the following lines in separate terminals:
```
roscore

rosrun ros_simple_gpio listener

rosrun ros_simple_gpio talker

```