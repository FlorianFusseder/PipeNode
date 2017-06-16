#include <iostream>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sensor_msgs/msg/image.hpp"

class BridgeNode: public rclcpp::node::Node
{
    public:
        BridgeNode() : Node("BridgeNode", true)
        {
            auto qos = rmw_qos_profile_sensor_data;
            publisher = this->create_publisher<sensor_msgs::msg::Image>
                ("/results/segmentation", qos);
            std::weak_ptr<std::remove_pointer<decltype(publisher.get())>::type>
                captured_publisher = publisher;
            subscribtion = this->create_subscription<sensor_msgs::msg::Image> (
                "/image", 
                std::bind(&BridgeNode::Sub_Callback, this, std::placeholders::_1)
                , qos);
        } 
    private:
        void Sub_Callback(sensor_msgs::msg::Image::SharedPtr msg)
        {
            std::cout << "I got a picture" << std::endl;
            // Pub_Callback(msg);
        }

        void Pub_Callback(sensor_msgs::msg::Image::SharedPtr msg)
        {
            msg->is_bigendian = false;
            std::cout <<"I publish: " << std::endl;
            // publisher->publish(msg);
        }

        rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscribtion;
        rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BridgeNode>());
    return 0;
}