#pragma once

#include <rws/RobWorkStudioPlugin.hpp>
#include "ui_rws_plugin_template.h"
#include <rw/models/WorkCell.hpp>
#include <rw/models/Device.hpp>
#include <rw/kinematics/Frame.hpp>

/*//////////////////////////////////////////////////////////////////////
 * 
 * ADD OTHER INCLUDES HERE
 * 
 /////////////////////////////////////////////////////////////////////*/

/*//////////////////////////////////////////////////////////////////////
 * 
 * Define plugin class.
 * CHANGE CLASS NAME, CTOR AND DTOR NAMES AS REQUIRED
 * 
 /////////////////////////////////////////////////////////////////////*/
class RwsPluginTemplate:
  public rws::RobWorkStudioPlugin
{
    
Q_OBJECT
Q_PLUGIN_METADATA(IID "dk.sdu.mip.Robwork.RobWorkStudioPlugin/0.1" FILE "plugin.json")
Q_INTERFACES(rws::RobWorkStudioPlugin)

public:
  RwsPluginTemplate();
  
  virtual ~RwsPluginTemplate();
  
  // Called when the plugin is loaded in RWS
  virtual void initialize() override;

  // Called when a workcell is opened in RWS
  virtual void open(rw::models::WorkCell* workcell) override;

  // Called when a workcell is closed in RWS
  virtual void close() override;
  
  /*////////////////////////////////////////////////////////////////////
   * 
   * DEFINE YOUR PUBLIC METHODS HERE
   * 
   ///////////////////////////////////////////////////////////////////*/

// Define methods for Qt GUI callbacks below
private slots:
  void onTestButtonClicked();

private:
  // Stores a pointer to the GUI
  Ui::PluginWidget* _ui;
  
  // Stores the pointer to the currently loaded workcell
  rw::models::WorkCell* _wc;
  
  /*////////////////////////////////////////////////////////////////////
   * 
   * DEFINE YOUR PRIVATE PROPERTIES HERE
   * 
   ///////////////////////////////////////////////////////////////////*/
};
