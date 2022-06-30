#include "ros/ros.h"
#include "geometry_msgs/Pose2D.h"

int x, y;

class K21semiAuto{
    private:
        ros::Publisher pose_pub;

    public:
        K21semiAuto(ros::NodeHandle *nh){
            pose_pub = nh->advertise<geometry_msgs::Pose2D>("/pose_test", 100);
            input();
        }
    
    void input(){
        geometry_msgs::Pose2D pose;

        std::cout << "input x: ";
        std::cin >> pose.x;
        std::cout << "input y: ";
        std::cin >> pose.y;
        
        pose_pub.publish(pose);
    }


};

int main(int argc, char** argv){
    ros::init(argc, argv, "k21_semiAuto");
    ros::NodeHandle nh;
    K21semiAuto semiauto = K21semiAuto(&nh);
    ros::spin(); 
    return 0;
}

