static const char *RcsId = "$Id:  $";
//+=============================================================================
//
// file :         PrincetonCCD.cpp
//
// description :  C++ source for the PrincetonCCD and its commands.
//                The class is derived from Device. It represents the
//                CORBA servant object which will be accessed from the
//                network. All commands which can be executed on the
//                PrincetonCCD are implemented in this file.
//
// project :      TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Revision:  $
// $Date:  $
//
// SVN only:
// $HeadURL: $
//
// CVS only:
// $Source:  $
// $Log:  $
//
// copyleft :    Synchrotron SOLEIL
//               L'Orme des merisiers - Saint Aubin
//               BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//-=============================================================================
//
//          This file is generated by POGO
//    (Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================



//===================================================================
//
//	The following table gives the correspondence
//	between commands and method name.
//
//  Command name|  Method name
//	----------------------------------------
//  State       |  dev_state()
//  Status      |  dev_status()
//  SetADCMode  |  set_adcmode()
//
//===================================================================
#ifdef WIN32
#include "tango.h"
#include <PogoHelper.h>
#endif
#include <PrincetonCCD.h>
#include <PrincetonCCDClass.h>

#ifndef WIN32
#include "tango.h"
#include <PogoHelper.h>
#endif

namespace PrincetonCCD_ns
{

//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::PrincetonCCD(string &s)
//
// description :     constructor for simulated PrincetonCCD
//
// in : - cl : Pointer to the DeviceClass object
//      - s : Device name
//
//-----------------------------------------------------------------------------
PrincetonCCD::PrincetonCCD(Tango::DeviceClass *cl,string &s)
:Tango::Device_4Impl(cl,s.c_str())
{
    init_device();
}

PrincetonCCD::PrincetonCCD(Tango::DeviceClass *cl,const char *s)
:Tango::Device_4Impl(cl,s)
{
    init_device();
}

PrincetonCCD::PrincetonCCD(Tango::DeviceClass *cl,const char *s,const char *d)
:Tango::Device_4Impl(cl,s,d)
{
    init_device();
}
//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::delete_device()
//
// description :     will be called at device destruction or at init command.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::delete_device()
{
    INFO_STREAM << "PrincetonCCD::PrincetonCCD() delete device " << device_name << endl;
    DELETE_SCALAR_ATTRIBUTE(attr_temperature_read);	
	DELETE_SCALAR_ATTRIBUTE(attr_temperatureTarget_read);	
    DELETE_SCALAR_ATTRIBUTE(attr_gain_read);    
	DELETE_DEVSTRING_ATTRIBUTE(attr_internalAcquisitionMode_read);	
	DELETE_DEVSTRING_ATTRIBUTE(attr_shutterMode_read);		
	DELETE_DEVSTRING_ATTRIBUTE(attr_currentRate_read);		

    //    Delete device allocated objects

    //!!!! ONLY LimaDetector device can do this !!!!
    //if(m_ct!=0)
    //{
    //    ControlFactory::instance().reset("PrincetonCCD");
    //    m_ct = 0;
    //}
}

//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::init_device()
//
// description :     will be called at device initialization.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::init_device()
{
    INFO_STREAM << "PrincetonCCD::PrincetonCCD() create device " << device_name << endl;

    // Initialise variables to default values
    //--------------------------------------------
    get_device_property();
	CREATE_SCALAR_ATTRIBUTE(attr_temperature_read, 0.0);
	CREATE_SCALAR_ATTRIBUTE(attr_temperatureTarget_read, 0.0);		
    CREATE_SCALAR_ATTRIBUTE(attr_gain_read);
	CREATE_DEVSTRING_ATTRIBUTE(attr_internalAcquisitionMode_read,MAX_ATTRIBUTE_STRING_LENGTH);	
	CREATE_DEVSTRING_ATTRIBUTE(attr_shutterMode_read,MAX_ATTRIBUTE_STRING_LENGTH);	
	CREATE_DEVSTRING_ATTRIBUTE(attr_currentRate_read,MAX_ATTRIBUTE_STRING_LENGTH);	
    m_is_device_initialized = false;
    set_state(Tango::INIT);
    m_status_message.str("");

    try
    {
        //- get the main object used to pilot the lima framework
        //in fact LimaDetector is create the singleton control objet
        //so this call, will only return existing object, no need to give it the ip !!
        m_ct = ControlFactory::instance().get_control("PrincetonCCD");

        //- get interface to specific camera
        m_hw = dynamic_cast<RoperScientific::Interface*>(m_ct->hwInterface());
        if(m_hw==0)
        {
            INFO_STREAM<<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PrincetonCCD"<<") !"<< endl;
            m_status_message <<"Initialization Failed : Unable to get the interface of camera plugin "<<"("<<"PrincetonCCD"<<") !"<< endl;
            m_is_device_initialized = false;
            set_state(Tango::FAULT);
            return;
        }
		
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		if(m_camera == 0)
		{
			INFO_STREAM<<"Initialization Failed : Unable to get the camera of plugin !"<<endl;
			m_status_message <<"Initialization Failed : Unable to get the camera object !"<< endl;
			m_is_device_initialized = false;
			set_state(Tango::FAULT);
			return;			
		}		
	
    }
    catch(Exception& e)
    {
        INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
        m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
    catch(...)
    {
        INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
        m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
	
	//write at init
	try
	{
		Tango::WAttribute &acquisitionMode = dev_attr->get_w_attr_by_name("internalAcquisitionMode");
		m_acquisition_mode = memorizedInternalAcquisitionMode;
		strcpy(*attr_internalAcquisitionMode_read,m_acquisition_mode.c_str());
		acquisitionMode.set_write_value(m_acquisition_mode);
		write_internalAcquisitionMode(acquisitionMode);
		
		Tango::WAttribute &shutterMode = dev_attr->get_w_attr_by_name("shutterMode");
		m_shutter_mode = memorizedShutterMode;
		strcpy(*attr_shutterMode_read,m_shutter_mode.c_str());
		shutterMode.set_write_value(m_shutter_mode);
		write_shutterMode(shutterMode);

		set_adcmode(memorizedADCMode);

		Tango::WAttribute &gain = dev_attr->get_w_attr_by_name("gain");
		gain.set_write_value(memorizedGain);
		write_gain(gain);
	}
    catch(Exception& e)
    {
        INFO_STREAM<<"Initialization Failed : "<<e.getErrMsg()<<endl;
        m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
        m_is_device_initialized = false;
        set_state(Tango::FAULT);
        return;
    }
    catch(...)
    {
        INFO_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
        m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
        set_state(Tango::FAULT);
        m_is_device_initialized = false;
        return;
    }
	
	m_is_device_initialized = true;		
    set_state(Tango::STANDBY);
    this->dev_state();
}


//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::get_device_property()
//
// description :     Read the device properties from database.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::get_device_property()
{
    //    Initialize your default values here (if not done with  POGO).
    //------------------------------------------------------------------

    //    Read device properties from database.(Automatic code generation)
    //------------------------------------------------------------------
	Tango::DbData	dev_prop;
	dev_prop.push_back(Tango::DbDatum("DetectorNum"));
	dev_prop.push_back(Tango::DbDatum("MemorizedInternalAcquisitionMode"));
	dev_prop.push_back(Tango::DbDatum("MemorizedShutterMode"));
	dev_prop.push_back(Tango::DbDatum("MemorizedGain"));
	dev_prop.push_back(Tango::DbDatum("MemorizedADCMode"));

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_device()->get_property(dev_prop);
	Tango::DbDatum	def_prop, cl_prop;
	PrincetonCCDClass	*ds_class =
		(static_cast<PrincetonCCDClass *>(get_device_class()));
	int	i = -1;

	//	Try to initialize DetectorNum from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  detectorNum;
	else {
		//	Try to initialize DetectorNum from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  detectorNum;
	}
	//	And try to extract DetectorNum value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  detectorNum;

	//	Try to initialize MemorizedInternalAcquisitionMode from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedInternalAcquisitionMode;
	else {
		//	Try to initialize MemorizedInternalAcquisitionMode from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedInternalAcquisitionMode;
	}
	//	And try to extract MemorizedInternalAcquisitionMode value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedInternalAcquisitionMode;

	//	Try to initialize MemorizedShutterMode from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedShutterMode;
	else {
		//	Try to initialize MemorizedShutterMode from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedShutterMode;
	}
	//	And try to extract MemorizedShutterMode value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedShutterMode;

	//	Try to initialize MemorizedGain from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedGain;
	else {
		//	Try to initialize MemorizedGain from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedGain;
	}
	//	And try to extract MemorizedGain value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedGain;

	//	Try to initialize MemorizedADCMode from class property
	cl_prop = ds_class->get_class_property(dev_prop[++i].name);
	if (cl_prop.is_empty()==false)	cl_prop  >>  memorizedADCMode;
	else {
		//	Try to initialize MemorizedADCMode from default device value
		def_prop = ds_class->get_default_device_property(dev_prop[i].name);
		if (def_prop.is_empty()==false)	def_prop  >>  memorizedADCMode;
	}
	//	And try to extract MemorizedADCMode value from database
	if (dev_prop[i].is_empty()==false)	dev_prop[i]  >>  memorizedADCMode;



    //    End of Automatic code generation
    //------------------------------------------------------------------
    create_property_if_empty(dev_prop,"-1","DetectorNum");
	create_property_if_empty(dev_prop,"STANDARD","MemorizedInternalAcquisitionMode");	
	create_property_if_empty(dev_prop,"OPEN_PRE_EXPOSURE","MemorizedShutterMode");	
    create_property_if_empty(dev_prop,"1","MemorizedGain");	    
	create_property_if_empty(dev_prop,"1","MemorizedADCMode");	    
	
}
//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::always_executed_hook()
//
// description :     method always executed before any command is executed
//
//-----------------------------------------------------------------------------
void PrincetonCCD::always_executed_hook()
{
	DEBUG_STREAM << "PrincetonCCD::always_executed_hook() entering... "<< endl;
	try
	{
	    m_status_message.str("");
		//- get the singleton control objet used to pilot the lima framework
		m_ct = ControlFactory::instance().get_control("PrincetonCCD");

		//- get interface to specific detector
		if(m_ct!=0)
			m_hw = dynamic_cast<RoperScientific::Interface*>(m_ct->hwInterface());
		//- get camera to specific detector
		m_camera = &(m_hw->getCamera());
		this->dev_state();

	}
	catch(Exception& e)
	{
		ERROR_STREAM << e.getErrMsg() << endl;
		m_status_message <<"Initialization Failed : "<<e.getErrMsg( )<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
	catch(...)
	{
		ERROR_STREAM<<"Initialization Failed : UNKNOWN"<<endl;
		m_status_message <<"Initialization Failed : UNKNOWN"<< endl;
		//- throw exception
		set_state(Tango::FAULT);
		m_is_device_initialized = false;
		return;
	}
}


//+----------------------------------------------------------------------------
//
// method :         PrincetonCCD::read_attr_hardware
//
// description :     Hardware acquisition for attributes.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_attr_hardware(vector<long> &attr_list)
{
    DEBUG_STREAM << "PrincetonCCD::read_attr_hardware(vector<long> &attr_list) entering... "<< endl;
    //    Add your own code here
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_internalAcquisitionMode
// 
// description : 	Extract real attribute values for internalAcquisitionMode acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_internalAcquisitionMode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_internalAcquisitionMode(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        std::string acq_mode = m_camera->getInternalAcqMode();
        strcpy(*attr_internalAcquisitionMode_read, acq_mode.c_str());
		
        attr.set_value(attr_internalAcquisitionMode_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::read_internalAcquisitionMode"));
    }		
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_internalAcquisitionMode"));
    }	 
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::write_internalAcquisitionMode
// 
// description : 	Write internalAcquisitionMode attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::write_internalAcquisitionMode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::write_internalAcquisitionMode(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        m_acquisition_mode = *attr_internalAcquisitionMode_read;
        string previous = m_acquisition_mode;
        attr.get_write_value(attr_internalAcquisitionMode_write);
        string current = attr_internalAcquisitionMode_write;
		/*TODO enhance CONTINUOUS*/
        if(current.compare("STANDARD")!=0 && current.compare("FOCUS")!=0/*&& current.compare("CONTINUOUS")!=0 */)
        {
            m_acquisition_mode = previous;
            attr_internalAcquisitionMode_write = new char [m_acquisition_mode.size()+1];
            strcpy (attr_internalAcquisitionMode_write, m_acquisition_mode.c_str());

            Tango::Except::throw_exception( (const char*) ("CONFIGURATION_ERROR"),
                                            /*(const char*) ("Available Internal Acquisition Modes are: \n- STANDARD \n- CONTINUOUS \n- FOCUS"),*/
											(const char*) ("Available Internal Acquisition Modes are: \n- STANDARD\n- FOCUS"),
                                            (const char*) ("PrincetonCCD::write_internalAcquisitionMode"));
        }

        //- THIS IS AN AVAILABLE ACQUISTION MODE
        m_acquisition_mode = attr_internalAcquisitionMode_write;

        m_camera->setInternalAcqMode(m_acquisition_mode);
        set_property("MemorizedInternalAcquisitionMode", m_acquisition_mode);

    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_internalAcquisitionMode"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_internalAcquisitionMode"));
    }	
}


//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_shutterMode
// 
// description : 	Extract real attribute values for shutterMode acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_shutterMode(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_shutterMode(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        int shutter_mode;
		m_camera->getShutterMode(shutter_mode);
		switch(shutter_mode)
		{
			case OPEN_NEVER : strcpy(*attr_shutterMode_read, "OPEN_NEVER");
			break;
			case OPEN_PRE_EXPOSURE : strcpy(*attr_shutterMode_read, "OPEN_PRE_EXPOSURE");
			break;			
			case OPEN_NO_CHANGE : strcpy(*attr_shutterMode_read, "OPEN_NO_CHANGE");
			break;			
		}

        attr.set_value(attr_shutterMode_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::read_shutterMode"));
    }			
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_shutterMode"));
    }	 
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::write_shutterMode
// 
// description : 	Write shutterMode attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::write_shutterMode(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::write_shutterMode(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        m_shutter_mode = *attr_shutterMode_read;
        string previous = m_shutter_mode;
        attr.get_write_value(attr_shutterMode_write);
        string current = attr_shutterMode_write;
		/*check user input*/
        if(current.compare("OPEN_NEVER")!=0 && current.compare("OPEN_PRE_EXPOSURE")!=0 && current.compare("OPEN_NO_CHANGE")!=0)
        {
            m_shutter_mode = previous;
            attr_shutterMode_write = new char [m_shutter_mode.size()+1];
            strcpy (attr_shutterMode_write, m_shutter_mode.c_str());

            Tango::Except::throw_exception( (const char*) ("CONFIGURATION_ERROR"),
                                            /*(const char*) ("Available Internal Acquisition Modes are: \n- OPEN_NEVER \n- OPEN_PRE_EXPOSURE \n- OPEN_NO_CHANGE"),*/
											(const char*) ("Available Shutter Modes are: \n- OPEN_NEVER \n- OPEN_PRE_EXPOSURE \n- OPEN_NO_CHANGE"),
                                            (const char*) ("PrincetonCCD::write_shutterMode"));
        }

        //- THIS IS AN AVAILABLE ACQUISTION MODE
        m_shutter_mode = attr_shutterMode_write;
        if(m_shutter_mode.compare("OPEN_NEVER")==0)
        {
			m_camera->setShutterMode(OPEN_NEVER);
        }

        if(m_shutter_mode.compare("OPEN_PRE_EXPOSURE")==0)
        {
			m_camera->setShutterMode(OPEN_PRE_EXPOSURE);
        }
		
        if(m_shutter_mode.compare("OPEN_NO_CHANGE")==0)
        {
			m_camera->setShutterMode(OPEN_NO_CHANGE);
        }
		

        set_property("MemorizedShutterMode", m_shutter_mode);

    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_shutterMode"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (e.getErrMsg().c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_shutterMode"));
    }		
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_temperatureTarget
// 
// description : 	Extract real attribute values for temperatureTarget acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_temperatureTarget(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_temperatureTarget(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        double temperatureTarget = 0.000;
       	temperatureTarget  = m_camera->getTemperatureSetPoint();
        *attr_temperatureTarget_read = temperatureTarget;
        attr.set_value(attr_temperatureTarget_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_temperatureTarget"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_temperatureTarget"));
    }		
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::write_temperatureTarget
// 
// description : 	Write temperatureTarget attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::write_temperatureTarget(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::write_temperatureTarget(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
        attr.get_write_value(attr_temperatureTarget_write);
       m_camera->setTemperatureSetPoint(attr_temperatureTarget_write);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_temperatureTarget"));
    }		
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::write_temperatureTarget"));
    }	
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_temperature
// 
// description : 	Extract real attribute values for temperature acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_temperature(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_temperature(Tango::Attribute &attr) entering... "<< endl;
    try
    {
        double temperature = 0.000;
       	temperature  = m_camera->getTemperature();
        *attr_temperature_read = temperature;
        attr.set_value(attr_temperature_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (string(df.errors[0].desc).c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_temperature"));
    }
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_temperature"));
    }	
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_gain
// 
// description : 	Extract real attribute values for gain acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_gain(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_gain(Tango::Attribute &attr) entering... "<< endl;	
    try
    {
		*attr_gain_read = (Tango::DevUShort)m_camera->getGain();		
        attr.set_value(attr_gain_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::read_gain"));
    }	    
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_gain"));
    }	
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::write_gain
// 
// description : 	Write gain attribute values to hardware.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::write_gain(Tango::WAttribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::write_gain(Tango::WAttribute &attr) entering... "<< endl;
    try
    {
       attr.get_write_value(attr_gain_write);
       m_camera->setGain(attr_gain_write);
       set_property("MemorizedGain", attr_gain_write);       
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::write_gain"));
    }		
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::write_gain"));
    }	    
}

//+----------------------------------------------------------------------------
//
// method : 		PrincetonCCD::read_currentRate
// 
// description : 	Extract real attribute values for currentRate acquisition result.
//
//-----------------------------------------------------------------------------
void PrincetonCCD::read_currentRate(Tango::Attribute &attr)
{
	DEBUG_STREAM << "PrincetonCCD::read_currentRate(Tango::Attribute &attr) entering... "<< endl;
    try
    {
		std::stringstream strRate("");
		//strRate<< "ADC mode = "<<m_camera->getSpeedTableIndex()<<" ( "<<m_camera->getADCRate()<<" )";
		strRate<< m_camera->getADCRate();
        strcpy(*attr_currentRate_read, (strRate.str()).c_str());
		
        attr.set_value(attr_currentRate_read);
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::read_currentRate"));
    }	
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::read_currentRate"));
    }	 
}


//+------------------------------------------------------------------
/**
 *	method:	PrincetonCCD::set_adcmode
 *
 *	description:	method to execute "SetADCMode"
 *	Define the ADC frequency .<br>
 *	Available values are :
 *	0-> 1MHz<br>
 *	1-> 100Khz
 *
 * @param	argin	
 *
 */
//+------------------------------------------------------------------
void PrincetonCCD::set_adcmode(Tango::DevUShort argin)
{
	DEBUG_STREAM << "PrincetonCCD::set_adcmode(): entering... !" << endl;

	//	Add your own code to control device here
    try
    {
       m_camera->setSpeedTableIndex(argin);
	   set_property("MemorizedADCMode", argin);   
    }
    catch(Tango::DevFailed& df)
    {
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                    static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                    static_cast<const char*> (string(df.errors[0].desc).c_str()),
                    static_cast<const char*> ("PrincetonCCD::set_adcmode"));
    }		
    catch(Exception& e)
    {
        ERROR_STREAM << e.getErrMsg() << endl;
        //- throw exception
        Tango::Except::throw_exception(
                     static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                     static_cast<const char*> (e.getErrMsg().c_str()),
                     static_cast<const char*> ("PrincetonCCD::set_adcmode"));
    }	
}    


//+------------------------------------------------------------------
/**
 *    method:    PrincetonCCD::dev_state
 *
 *    description:    method to execute "State"
 *    This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *
 * @return    State Code
 *
 */
//+------------------------------------------------------------------
Tango::DevState PrincetonCCD::dev_state()
{
    Tango::DevState    argout = DeviceImpl::dev_state();
    DEBUG_STREAM << "PrincetonCCD::dev_state(): entering... !" << endl;
    
    
    //    Add your own code to control device here

    stringstream    DeviceStatus;
    DeviceStatus     << "";
    Tango::DevState DeviceState    = Tango::STANDBY;
    if(!m_is_device_initialized )
    {
        DeviceState            = Tango::FAULT;
        DeviceStatus        << m_status_message.str();
    }
    else
	{
		//state&status are retrieved from specific device
		DeviceState = ControlFactory::instance().get_state();
		DeviceStatus << ControlFactory::instance().get_status();		
    }

    set_state(DeviceState);
    set_status(DeviceStatus.str());

    argout = DeviceState;

    return argout;
}



/*-------------------------------------------------------------------------
//       PrincetonCCD::set_property
/-------------------------------------------------------------------------*/
template <class T>
void PrincetonCCD::set_property(string property_name, T value)
{
    if (!Tango::Util::instance()->_UseDb)
    {
        //- rethrow exception
        Tango::Except::throw_exception(static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                                       static_cast<const char*> ("NO DB"),
                                       static_cast<const char*> ("PrincetonCCD::set_property"));
    }    
    
    Tango::DbDatum current_value(property_name);
    current_value << value;
    Tango::DbData db_data;
    db_data.push_back(current_value);
    try
    {
        get_db_device()->put_property(db_data);
    }
    catch (Tango::DevFailed &df)
    {
        string message = "Error in storing " + property_name + " in Configuration DataBase ";
        LOG_ERROR((message));
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                                          static_cast<const char*> (string(df.errors[0].desc).c_str()),
                                          static_cast<const char*> ("PrincetonCCD::set_property"));
    }
}

/*-------------------------------------------------------------------------
//       PrincetonCCD::get_property
/-------------------------------------------------------------------------*/
template <class T>
T PrincetonCCD::get_property(string property_name)
{
    if (!Tango::Util::instance()->_UseDb)
    {
        //- rethrow exception
        Tango::Except::throw_exception(static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                                       static_cast<const char*> ("NO DB"),
                                       static_cast<const char*> ("PrincetonCCD::get_property"));
    }     
    
    T value;
    Tango::DbDatum current_value(property_name);    
    Tango::DbData db_data;
    db_data.push_back(current_value);
    try
    {
        get_db_device()->get_property(db_data);
    }
    catch (Tango::DevFailed &df)
    {
        string message = "Error in reading " + property_name + " in Configuration DataBase ";
        LOG_ERROR((message));
        ERROR_STREAM << df << endl;
        //- rethrow exception
        Tango::Except::re_throw_exception(df,
                                          static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                                          static_cast<const char*> (string(df.errors[0].desc).c_str()),
                                          static_cast<const char*> ("PrincetonCCD::get_property"));
    }
    db_data[0] >> value;
    return (value);
}
/*-------------------------------------------------------------------------
//       PrincetonCCD::create_property_if_empty
/-------------------------------------------------------------------------*/
template <class T>
void PrincetonCCD::create_property_if_empty(Tango::DbData& dev_prop,T value,string property_name)
{
    int iPropertyIndex = find_index_from_property_name(dev_prop,property_name);
    if (iPropertyIndex == -1) return;
    if (dev_prop[iPropertyIndex].is_empty())
    {
        Tango::DbDatum current_value(dev_prop[iPropertyIndex].name);
        current_value << value;
        Tango::DbData db_data;
        db_data.push_back(current_value);

        try
        {
            get_db_device()->put_property(db_data);
        }
        catch(Tango::DevFailed &df)
        {
            string message= "Error in storing " + property_name + " in Configuration DataBase ";
            LOG_ERROR((message));
            ERROR_STREAM<<df<<endl;
            //- rethrow exception
            Tango::Except::re_throw_exception(df,
                        static_cast<const char*> ("TANGO_DEVICE_ERROR"),
                        static_cast<const char*> (string(df.errors[0].desc).c_str()),
                        static_cast<const char*> ("PrincetonCCD::create_property_if_empty"));
        }
    }
}


/*-------------------------------------------------------------------------
//       PrincetonCCD::find_index_from_property_name
/-------------------------------------------------------------------------*/
int PrincetonCCD::find_index_from_property_name(Tango::DbData& dev_prop, string property_name)
{
    size_t iNbProperties = dev_prop.size();
    unsigned int i;
    for (i=0;i<iNbProperties;i++)
    {
        string sPropertyName(dev_prop[i].name);
        if (sPropertyName == property_name) return i;
    }
    if (i == iNbProperties) return -1;
    return i;
}







}	//	namespace
