#include <pick_and_place.hpp>

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pick_and_place");

    ros::AsyncSpinner spinner(2);
    spinner.start();

    ros::NodeHandle nh;
    Pick_and_Place pnp(nh);

    ros::waitForShutdown();
    ros::shutdown();
    return 0;
}