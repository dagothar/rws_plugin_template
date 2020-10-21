RobWorkStudio plugin template
=============================

1. Installation
---------------

After installing the RobWork suite, you need to set the environment variables
pointing to the RobWork modules root directories. Add the following lines to your
.bashrc:

    export RW_ROOT=${HOME}/robwork/RobWork
    export RWS_ROOT=${HOME}/robwork/RobWorkStudio
    export RWSIM_ROOT=${HOME}/robwork/RobWorkSim

(Change the path as required.)

2. Building
-----------

    cd <plugin_path>/build
    cmake ..
    make

3. Using
--------

You can add the plugin using Plugins -> Load plugin menu action.
The better way is to add an entry to your '[Plugins]' section of the RobWorkStudio.ini file as below:

    RWSPluginTemplate\DockArea=2
    RWSPluginTemplate\Filename=librws_plugin_template.so
    RWSPluginTemplate\Path=<plugin path>/libs
    RWSPluginTemplate\Visible=true

Change the RWSPluginTemplate in the snippet above to an unique name!

If you should like to have a specific workcell loaded whenever you launch RobWorkStudio,
add the following section to your RobWorkStudio.ini file:

    [Settings]
    Workcell\Path=<workcell path>/scene.wc.xml

3. Modifying
------------

WIP
