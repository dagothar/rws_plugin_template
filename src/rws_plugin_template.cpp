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
  // Create GUI
  _ui = new Ui::PluginWidget;
  _ui->setupUi(this);
  
  /* polacz kontrolki z metodami */
  //connect(kursorButton, SIGNAL(clicked()), this, SLOT(kursor()));
  //connect(ikButton, SIGNAL(clicked()), this, SLOT(ik()));
}


RwsPluginTemplate::~RwsPluginTemplate() {
}


void RwsPluginTemplate::initialize() {
}


void RwsPluginTemplate::open(rw::models::WorkCell* workcell) {
  /* zapisz wskaźnik do komórki roboczej i domyślny stan */
  _wc = workcell;
  
  /* znajdź robota */
  /*_robot = _wc->findDevice("ur5");
  if (_robot) {
    Log::log().info() << "Znaleziono urządzenie: " << _robot->getName() << endl;
  }
  
  Frame* kursor = _wc->findFrame("kursor");
  if (kursor)
    getRobWorkStudio()->getWorkCellScene()->setFrameAxisVisible(true, kursor);*/
}


void RwsPluginTemplate::close() {
  _wc = nullptr;
}






void RwsPluginTemplate::kursor() {
  MovableFrame* kursor = _wc->findFrame<MovableFrame>("kursor");
  if (!kursor) {
    Log::log().warning() << "Nie znaleziono ukladu kursor!" << endl;
    return;
  }
  
  if (!_robot) {
    Log::log().warning() << "Nie znaleziono robota!" << endl;
    return;
  }
  
  State state = getRobWorkStudio()->getState();
  kursor->setTransform(_robot->baseTend(state), state);
  getRobWorkStudio()->setState(state);
  
  QSampler::Ptr sampler = QSampler::makeUniform(_robot);
  Log::log().info() << sampler->sample() << endl;
}


void RwsPluginTemplate::ik() {
  Frame* kursor = _wc->findFrame("kursor");
  if (!kursor) {
    Log::log().warning() << "Nie znaleziono ukladu kursor!" << endl;
    return;
  }
  
  State state = getRobWorkStudio()->getState();
  Transform3D<> Tkursor = Kinematics::worldTframe(kursor, state);
  Log::log().info() << "Wspolrzedne: " << Tkursor << endl;
  
  Metric<Transform3D<>>::Ptr metric = MetricFactory::makeTransform3DMetric<double>(1.0, 1.0);
  
  Q q = _robot->getQ(state);
  int iteracje = 0;
  double error;
  do {
    Transform3D<> Ttcp = _robot->baseTend(state);
    Transform3D<> Terror = inverse(Ttcp) * Tkursor;
    VelocityScrew6D<> Verror(Terror);
    //EAA<> eaa(Terror(2,1), Terror(0,2), Terror(1,0));
    //VelocityScrew6D<> Verror(Terror.P(), eaa);
    //Verror = Ttcp.R() * Verror;
    Log::log().info() << Verror << endl;
    
    Jacobian jacobian = _robot->baseJCend(state)->get(state);
    Eigen::MatrixXd jac = jacobian.e();
    
    Eigen::VectorXd temp = jac.inverse() * Verror.e();
    Q dq(temp);
    q += dq;
    
    _robot->setQ(q, state);
    
    error = metric->distance(Terror);
    ++iteracje;
  } while (error > 0.001 && iteracje < 1);
  
  Log::log().info() << "Ilość iteracji: " << iteracje << " Blad: " << error << endl;
  
  _robot->setQ(q, state);
  getRobWorkStudio()->setState(state);
}
