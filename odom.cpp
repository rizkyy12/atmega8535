#include "ros/ros.h"
#include "nav_msgs/Odometry.h"
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Pose2D.h"
#include "std_msgs/Float64.h"

ros::Publisher pub1;
ros::Publisher pub2;
ros::Publisher pub3;

ros::Subscriber odom_subs;
ros::Subscriber input_subs;

geometry_msgs::Vector3 data_enc;
geometry_msgs::Pose2D data_input;

float x_pos, y_pos, z_pos, MV_X, MV_Y, MV_Z;
float pv_x, pv_y, pv_z;
int x_max = 392;
int y_max = 375;
int z_max = 3407;
int KpX = 3, KpY = 3, KpZ = 10;
int x_target, y_target, z_target;
float errorX, errorY, errorZ;

void odom_Cb(const geometry_msgs::Vector3::ConstPtr &msg);
void inputCb(const geometry_msgs::Pose2D::ConstPtr &msg);

int main(int argc, char **argv){
    ros::init(argc, argv, "robot_odom");

    ros::NodeHandle nh;

    pub1 = nh.advertise<std_msgs::Float64>("/Polebot/V1_controller/command", 1000);
    pub2 = nh.advertise<std_msgs::Float64>("/Polebot/V2_controller/command", 1000);
    pub3 = nh.advertise<std_msgs::Float64>("/Polebot/V3_controller/command", 1000);

    odom_subs = nh.subscribe("/pulse_encoder", 10, odom_Cb);
    input_subs = nh.subscribe("/pose_input", 10, inputCb);

    ros::Rate loop_rate(0.5);
    ros::spin();
    return 0;
}

void odom_Cb(const geometry_msgs::Vector3::ConstPtr &msg){
    nav_msgs::Odometry odom;
    std_msgs::Float64 vel1;
    std_msgs::Float64 vel2;
    std_msgs::Float64 vel3;
    

    data_enc.x = msg->x;
    data_enc.y = msg->y;
    data_enc.z = msg->z;

    x_pos = -0.5 * msg->x - 0.5 *msg->y + 1 * msg->z;
    y_pos = 0.866 * msg->x - 0.866 *msg->y;
    z_pos = msg->x + msg->y + 1.5 * msg->z;

    pv_x = 30 * (x_pos/x_max);
    pv_y = 30 * (y_pos/y_max);
    pv_z = 360 * (z_pos/z_max);

    if (pv_z >= 360){
        pv_z = 0;
    }
    else if(pv_z <= -360){
        pv_z = 0;
    }

    errorX = x_target - pv_x;
    errorY = y_target - pv_y;
    errorZ = (z_target*-1) - pv_z;

    MV_X = KpX * errorX;
    MV_Y = KpY * errorY;
    MV_Z = KpZ * errorZ;

    if (MV_X >= 400){
        MV_X = 400;
    }
    else if(MV_X <= -400){
        MV_X = -400;
    }

    if (MV_Y >= 400){
        MV_Y = 400;
    }
    else if(MV_Y <= -400){
        MV_Y = -400;
    }

    vel1.data = -0.333 * MV_X + 0.5774 * MV_Y + 0.045* MV_Z;
    vel2.data = -0.333 * MV_X - 0.5774 * MV_Y + 0.045* MV_Z;
    vel3.data = 0.667 * MV_X + 0.045*MV_Z;

    ROS_INFO("V1: %f", vel1.data);
    ROS_INFO("V2: %f", vel2.data);
    ROS_INFO("V3: %f", vel3.data);

    pub1.publish(vel1);
    pub2.publish(vel2);
    pub3.publish(vel3);
}

void inputCb(const geometry_msgs::Pose2D::ConstPtr &msg){
    x_target = msg->x;
    y_target = msg->y;
    z_target = msg->theta;
}
