#include <iostream>
#include <memory>

// #include "opencv2/opencv.hpp"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"

class BridgeNode: public rclcpp::node::Node
{
    public:
        BridgeNode() : Node("BridgeNode", true)
        {
            auto qos = rmw_qos_profile_sensor_data;
            auto pubStr = "image";
            auto subStr = "watermarked_image";
            publisher = this->create_publisher<sensor_msgs::msg::Image>
                (subStr, qos);
            captured_publisher = publisher;
            subscribtion = this->create_subscription<sensor_msgs::msg::Image> (
                pubStr, 
                std::bind(&BridgeNode::Sub_Callback, this, std::placeholders::_1),
                qos);
        } 
    private:
        void Sub_Callback(sensor_msgs::msg::Image::UniquePtr msg)
        {
            auto p = captured_publisher.lock();
            if(!p)
                return;
            p->publish(msg);
        }

        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscribtion;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher;
        std::weak_ptr<std::remove_pointer<decltype(publisher.get())>::type> captured_publisher;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BridgeNode>());
    return 0;
}