/*//////////////////////////////////////////////////////////////////////
 * 
 * CHANGE THIS INCLUDE ACCORDING TO HEADER FILENAME
 * 
 /////////////////////////////////////////////////////////////////////*/
#include "rws_plugin_template.hpp"

#include <rws/RobWorkStudio.hpp>

/*//////////////////////////////////////////////////////////////////////
 * 
 * ADD OTHER INCLUDES HERE
 * 
 /////////////////////////////////////////////////////////////////////*/


using namespace std;
using namespace rw::models;
using namespace rw::kinematics;
using namespace rw::math;
using namespace rw::common;
using namespace rw::core;

/*//////////////////////////////////////////////////////////////////////
 * 
 * ADD OTHER NAMESPACES HERE
 * 
 /////////////////////////////////////////////////////////////////////*/


RwsPluginTemplate::RwsPluginTemplate() :
  RobWorkStudioPlugin("RwsPluginTemplate", QIcon(":/picon.png"))
{
  /*
   * Create GUI instance
   */
  _ui = new Ui::PluginWidget;
  _ui->setupUi(this);
  
  /*
   * Connect widgets (e.g. buttons) to methods in the class.
   */
  connect(_ui->testButton, SIGNAL(clicked()), this, SLOT(onTestButtonClicked()));
}


RwsPluginTemplate::~RwsPluginTemplate() {
  delete _ui;
}


void RwsPluginTemplate::initialize() {
}


void RwsPluginTemplate::open(rw::models::WorkCell* workcell) {
  /*
   * This method is called when a workcell is loaded in RWS environment.
   * Save the argument as the private property for further use.
   */
  _wc = workcell;
  
  /*
   * Example:
   * This is how to find a device (e.g. a robot in the workcell.
   * 'device' should be declared as a private property if you would like
   *  to access it elsewhere in the class.
   */
  rw::models::Device::Ptr robot = _wc->findDevice("ur5");
  if (robot) {
    Log::log().info() << "Device found: " << robot->getName() << endl;
  } else {
    Log::log().warning() << "Device not found!" << endl;
  }
  
  /*
   * Example:
   * This is how to find a frame in the workcell.
   * 'frame' should be declared as a private property if you would like
   *  to access it elsewhere in the class.
   * If you want to change the frame pose, it should be defined as
   * a Movable frame type in the workcell.
   */
  rw::kinematics::Frame* frame = _wc->findFrame("frame");
  // rw::kinematics::MovableFrame* frame = _wc->findFrame<rw::kinematics::MovableFrame>("frame");
  if (frame) {
    // Example: sets the frame axes visible in the RWS environment.
    getRobWorkStudio()->getWorkCellScene()->setFrameAxisVisible(true, frame);
  }
}


void RwsPluginTemplate::close() {
  /*
   * Define what happens when the workcell is closed.
   * You will likely want to clear the pointers to objects that
   * no longer exist.
   */
  _wc = nullptr;
}


void RwsPluginTemplate::onTestButtonClicked() {
  Log::log().info() << "Test button clicked!" << endl;
}
