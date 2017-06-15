#include <iostream>

#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class BridgeNode: public rclcpp::node::Node
{
    public:
        BridgeNode() : Node("BridgeNode")
        {
            publisher = this->create_publisher<std_msgs::msg::String>("chatter1");
            subscribtion = this->create_subscription<std_msgs::msg::String>("chatter2", 
                std::bind(&BridgeNode::Sub_Callback, this, std::placeholders::_1));
        } 
    private:
        void Sub_Callback(std_msgs::msg::String::SharedPtr msg)
        {
            std::cout << "I got: " + msg->data << std::endl;
            Pub_Callback(msg);
        }

        void Pub_Callback(std_msgs::msg::String::SharedPtr msg)
        {
            std::cout <<"I publish: " + msg->data << std::endl;
            publisher->publish(msg);
        }


        rclcpp::subscription::Subscription<std_msgs::msg::String>::SharedPtr subscribtion;
        rclcpp::publisher::Publisher<std_msgs::msg::String>::SharedPtr publisher;
};

int main(int argc, char* argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<BridgeNode>());
    return 0;
}