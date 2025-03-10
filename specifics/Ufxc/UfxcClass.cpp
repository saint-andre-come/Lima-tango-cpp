static const char *ClassId    = "$Id:  $";
static const char *TagName    = "$Name:  $";
static const char *CvsPath    = "$Source:  $";
static const char *SvnPath    = "$HeadURL: $";
static const char *HttpServer = "http://www.esrf.fr/computing/cs/tango/tango_doc/ds_doc/";
//+=============================================================================
//
// file :        UfxcClass.cpp
//
// description : C++ source for the UfxcClass. A singleton
//               class derived from DeviceClass. It implements the
//               command list and all properties and methods required
//               by the Ufxc once per process.
//
// project :     TANGO Device Server
//
// $Author:  $
//
// $Revision:  $
//
// $Log:  $
//
// copyleft :   European Synchrotron Radiation Facility
//              BP 220, Grenoble 38043
//              FRANCE
//
//-=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================


#ifdef WIN32
#include "tango.h"
#endif
#include <Ufxc.h>
#include <UfxcClass.h>

#ifndef WIN32
#include "tango.h"
#endif

//+----------------------------------------------------------------------------
/**
 *	Create UfxcClass singleton and return it in a C function for Python usage
 */
//+----------------------------------------------------------------------------
extern "C" {
#ifdef WIN32

__declspec(dllexport)

#endif

	Tango::DeviceClass *_create_Ufxc_class(const char *name) {
		return Ufxc_ns::UfxcClass::init(name);
	}
}


namespace Ufxc_ns
{
//+----------------------------------------------------------------------------
//
// method : 		LoadConfigFileClass::execute()
// 
// description : 	method to trigger the execution of the command.
//                PLEASE DO NOT MODIFY this method core without pogo   
//
// in : - device : The device on which the command must be executed
//		- in_any : The command input data
//
// returns : The command output data (packed in the Any object)
//
//-----------------------------------------------------------------------------
CORBA::Any *LoadConfigFileClass::execute(Tango::DeviceImpl *device,const CORBA::Any &in_any)
{

	cout2 << "LoadConfigFileClass::execute(): arrived" << endl;

	Tango::DevString	argin;
	extract(in_any, argin);

	((static_cast<Ufxc *>(device))->load_config_file(argin));
	return new CORBA::Any();
}


















//
//----------------------------------------------------------------
//	Initialize pointer for singleton pattern
//----------------------------------------------------------------
//
UfxcClass *UfxcClass::_instance = NULL;

//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::UfxcClass(string &s)
// 
// description : 	constructor for the UfxcClass
//
// in : - s : The class name
//
//-----------------------------------------------------------------------------
UfxcClass::UfxcClass(string &s):DeviceClass(s)
{

	cout2 << "Entering UfxcClass constructor" << endl;
	set_default_property();
	get_class_property();
	write_class_property();
	
	cout2 << "Leaving UfxcClass constructor" << endl;

}
//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::~UfxcClass()
// 
// description : 	destructor for the UfxcClass
//
//-----------------------------------------------------------------------------
UfxcClass::~UfxcClass()
{
	_instance = NULL;
}

//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::instance
// 
// description : 	Create the object if not already done. Otherwise, just
//			return a pointer to the object
//
// in : - name : The class name
//
//-----------------------------------------------------------------------------
UfxcClass *UfxcClass::init(const char *name)
{
	if (_instance == NULL)
	{
		try
		{
			string s(name);
			_instance = new UfxcClass(s);
		}
		catch (bad_alloc)
		{
			throw;
		}		
	}		
	return _instance;
}

UfxcClass *UfxcClass::instance()
{
	if (_instance == NULL)
	{
		cerr << "Class is not initialised !!" << endl;
		exit(-1);
	}
	return _instance;
}

//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::command_factory
// 
// description : 	Create the command object(s) and store them in the 
//			command list
//
//-----------------------------------------------------------------------------
void UfxcClass::command_factory()
{
	command_list.push_back(new LoadConfigFileClass("LoadConfigFile",
		Tango::DEV_STRING, Tango::DEV_VOID,
		"alias of the Detector configuration file",
		"",
		Tango::OPERATOR));

	//	add polling if any
	for (unsigned int i=0 ; i<command_list.size(); i++)
	{
	}
}

//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::get_class_property
// 
// description : 	Get the class property for specified name.
//
// in :		string	name : The property name
//
//+----------------------------------------------------------------------------
Tango::DbDatum UfxcClass::get_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_prop.size() ; i++)
		if (cl_prop[i].name == prop_name)
			return cl_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::get_default_device_property()
// 
// description : 	Return the default value for device property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum UfxcClass::get_default_device_property(string &prop_name)
{
	for (unsigned int i=0 ; i<dev_def_prop.size() ; i++)
		if (dev_def_prop[i].name == prop_name)
			return dev_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}

//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::get_default_class_property()
// 
// description : 	Return the default value for class property.
//
//-----------------------------------------------------------------------------
Tango::DbDatum UfxcClass::get_default_class_property(string &prop_name)
{
	for (unsigned int i=0 ; i<cl_def_prop.size() ; i++)
		if (cl_def_prop[i].name == prop_name)
			return cl_def_prop[i];
	//	if not found, return  an empty DbDatum
	return Tango::DbDatum(prop_name);
}
//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::device_factory
// 
// description : 	Create the device object(s) and store them in the 
//			device list
//
// in :		Tango::DevVarStringArray *devlist_ptr : The device name list
//
//-----------------------------------------------------------------------------
void UfxcClass::device_factory(const Tango::DevVarStringArray *devlist_ptr)
{

	//	Create all devices.(Automatic code generation)
	//-------------------------------------------------------------
	for (unsigned long i=0 ; i < devlist_ptr->length() ; i++)
	{
		cout4 << "Device name : " << (*devlist_ptr)[i].in() << endl;
						
		// Create devices and add it into the device list
		//----------------------------------------------------
		device_list.push_back(new Ufxc(this, (*devlist_ptr)[i]));							 

		// Export device to the outside world
		// Check before if database used.
		//---------------------------------------------
		if ((Tango::Util::_UseDb == true) && (Tango::Util::_FileDb == false))
			export_device(device_list.back());
		else
			export_device(device_list.back(), (*devlist_ptr)[i]);
	}
	//	End of Automatic code generation
	//-------------------------------------------------------------

}
//+----------------------------------------------------------------------------
//	Method: UfxcClass::attribute_factory(vector<Tango::Attr *> &att_list)
//-----------------------------------------------------------------------------
void UfxcClass::attribute_factory(vector<Tango::Attr *> &att_list)
{
	//	Attribute : libVersion
	libVersionAttrib	*lib_version = new libVersionAttrib();
	Tango::UserDefaultAttrProp	lib_version_prop;
	lib_version_prop.set_unit("  ");
	lib_version_prop.set_standard_unit("  ");
	lib_version_prop.set_display_unit("  ");
	lib_version_prop.set_description("Display the Ufxc Library Version.");
	lib_version->set_default_properties(lib_version_prop);
	lib_version->set_disp_level(Tango::EXPERT);
	att_list.push_back(lib_version);

	//	Attribute : firmwareVersion
	firmwareVersionAttrib	*firmware_version = new firmwareVersionAttrib();
	Tango::UserDefaultAttrProp	firmware_version_prop;
	firmware_version_prop.set_unit(" ");
	firmware_version_prop.set_standard_unit(" ");
	firmware_version_prop.set_display_unit(" ");
	firmware_version_prop.set_description("Dis^lay the firmware version of the DAQ");
	firmware_version->set_default_properties(firmware_version_prop);
	firmware_version->set_disp_level(Tango::EXPERT);
	att_list.push_back(firmware_version);

	//	Attribute : currentAlias
	currentAliasAttrib	*current_alias = new currentAliasAttrib();
	Tango::UserDefaultAttrProp	current_alias_prop;
	current_alias_prop.set_unit(" ");
	current_alias_prop.set_standard_unit(" ");
	current_alias_prop.set_display_unit(" ");
	current_alias_prop.set_format("%s");
	current_alias_prop.set_description("Display the current Alias used to load the configuration file.");
	current_alias->set_default_properties(current_alias_prop);
	att_list.push_back(current_alias);

	//	Attribute : currentConfigFile
	currentConfigFileAttrib	*current_config_file = new currentConfigFileAttrib();
	Tango::UserDefaultAttrProp	current_config_file_prop;
	current_config_file_prop.set_unit(" ");
	current_config_file_prop.set_standard_unit(" ");
	current_config_file_prop.set_display_unit(" ");
	current_config_file_prop.set_format("%s");
	current_config_file_prop.set_description("Display the path+name of current configuration file.");
	current_config_file->set_default_properties(current_config_file_prop);
	att_list.push_back(current_config_file);

	//	Attribute : detectorTemperature
	detectorTemperatureAttrib	*detector_temperature = new detectorTemperatureAttrib();
	Tango::UserDefaultAttrProp	detector_temperature_prop;
	detector_temperature_prop.set_unit("Celsius");
	detector_temperature_prop.set_standard_unit("Celsius");
	detector_temperature_prop.set_display_unit("?C");
	detector_temperature_prop.set_description("Display the detector temperature in degree Celsius ");
	detector_temperature->set_default_properties(detector_temperature_prop);
	att_list.push_back(detector_temperature);

	//	Attribute : thresholdLow
	thresholdLowAttrib	*threshold_low = new thresholdLowAttrib();
	Tango::UserDefaultAttrProp	threshold_low_prop;
	threshold_low_prop.set_unit("keV");
	threshold_low_prop.set_standard_unit("keV");
	threshold_low_prop.set_display_unit("keV");
	threshold_low_prop.set_description("Set threshold Low for the chip A & chip B");
	threshold_low->set_default_properties(threshold_low_prop);
	att_list.push_back(threshold_low);

	//	Attribute : thresholdHigh
	thresholdHighAttrib	*threshold_high = new thresholdHighAttrib();
	Tango::UserDefaultAttrProp	threshold_high_prop;
	threshold_high_prop.set_unit("keV");
	threshold_high_prop.set_standard_unit("keV");
	threshold_high_prop.set_display_unit("keV");
	threshold_high_prop.set_description("Set threshold High for the chip A & chip B");
	threshold_high->set_default_properties(threshold_high_prop);
	att_list.push_back(threshold_high);

	//	Attribute : thresholdLow1
	thresholdLow1Attrib	*threshold_low1 = new thresholdLow1Attrib();
	Tango::UserDefaultAttrProp	threshold_low1_prop;
	threshold_low1_prop.set_unit("mV");
	threshold_low1_prop.set_standard_unit("mV");
	threshold_low1_prop.set_display_unit("mV");
	threshold_low1_prop.set_description("Get threshold Low  for the chip A");
	threshold_low1->set_default_properties(threshold_low1_prop);
	att_list.push_back(threshold_low1);

	//	Attribute : thresholdHigh1
	thresholdHigh1Attrib	*threshold_high1 = new thresholdHigh1Attrib();
	Tango::UserDefaultAttrProp	threshold_high1_prop;
	threshold_high1_prop.set_unit("mV");
	threshold_high1_prop.set_standard_unit("mV");
	threshold_high1_prop.set_display_unit("mV");
	threshold_high1_prop.set_description("Get threshold High for the chip A");
	threshold_high1->set_default_properties(threshold_high1_prop);
	att_list.push_back(threshold_high1);

	//	Attribute : thresholdLow2
	thresholdLow2Attrib	*threshold_low2 = new thresholdLow2Attrib();
	Tango::UserDefaultAttrProp	threshold_low2_prop;
	threshold_low2_prop.set_unit("mV");
	threshold_low2_prop.set_standard_unit("mV");
	threshold_low2_prop.set_display_unit("mV");
	threshold_low2_prop.set_description("Get threshold Low for the chip B");
	threshold_low2->set_default_properties(threshold_low2_prop);
	att_list.push_back(threshold_low2);

	//	Attribute : thresholdHigh2
	thresholdHigh2Attrib	*threshold_high2 = new thresholdHigh2Attrib();
	Tango::UserDefaultAttrProp	threshold_high2_prop;
	threshold_high2_prop.set_unit("mV");
	threshold_high2_prop.set_standard_unit("mV");
	threshold_high2_prop.set_display_unit("mV");
	threshold_high2_prop.set_description("Get threshold High for the chip B");
	threshold_high2->set_default_properties(threshold_high2_prop);
	att_list.push_back(threshold_high2);

	//	Attribute : triggerAcquisitionFrequency
	triggerAcquisitionFrequencyAttrib	*trigger_acquisition_frequency = new triggerAcquisitionFrequencyAttrib();
	Tango::UserDefaultAttrProp	trigger_acquisition_frequency_prop;
	trigger_acquisition_frequency_prop.set_unit("Hz");
	trigger_acquisition_frequency_prop.set_standard_unit(" ");
	trigger_acquisition_frequency_prop.set_display_unit(" ");
	trigger_acquisition_frequency_prop.set_description("Define the trigger acquisition frequency in the pump & probe mode");
	trigger_acquisition_frequency->set_default_properties(trigger_acquisition_frequency_prop);
	att_list.push_back(trigger_acquisition_frequency);

	//	End of Automatic code generation
	//-------------------------------------------------------------
}



//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::get_class_property()
// 
// description : 	Read the class properties from database.
//
//-----------------------------------------------------------------------------
void UfxcClass::get_class_property()
{
	//	Initialize your default values here (if not done with  POGO).
	//------------------------------------------------------------------

	//	Read class properties from database.(Automatic code generation)
	//------------------------------------------------------------------

	//	Call database and extract values
	//--------------------------------------------
	if (Tango::Util::instance()->_UseDb==true)
		get_db_class()->get_property(cl_prop);
	Tango::DbDatum	def_prop;
	int	i = -1;


	//	End of Automatic code generation
	//------------------------------------------------------------------

}

//+----------------------------------------------------------------------------
//
// method : 	UfxcClass::set_default_property
// 
// description: Set default property (class and device) for wizard.
//              For each property, add to wizard property name and description
//              If default value has been set, add it to wizard property and
//              store it in a DbDatum.
//
//-----------------------------------------------------------------------------
void UfxcClass::set_default_property()
{
	string	prop_name;
	string	prop_desc;
	string	prop_def;

	vector<string>	vect_data;
	//	Set Default Class Properties
	//	Set Default Device Properties
	prop_name = "AutoLoad";
	prop_desc = "Allow to Reload the last used Detector Configuration file at each init of the device.";
	prop_def  = "False";
	vect_data.clear();
	vect_data.push_back("False");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "ConfigIpAddress";
	prop_desc = "Config Ip Address";
	prop_def  = "127.0.0.1";
	vect_data.clear();
	vect_data.push_back("127.0.0.1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "ConfigPort";
	prop_desc = "Config Port";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP1IpAddress";
	prop_desc = "SFP1 Ip Address";
	prop_def  = "127.0.0.1";
	vect_data.clear();
	vect_data.push_back("127.0.0.1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP1Port";
	prop_desc = "SFP1 Port";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP2IpAddress";
	prop_desc = "SFP2 Ip Address";
	prop_def  = "127.0.0.1";
	vect_data.clear();
	vect_data.push_back("127.0.0.1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP2Port";
	prop_desc = "SFP2 Port";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP3IpAddress";
	prop_desc = "SFP3 Ip Address";
	prop_def  = "127.0.0.1";
	vect_data.clear();
	vect_data.push_back("127.0.0.1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "SFP3Port";
	prop_desc = "SFP3 Port";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "Timeout";
	prop_desc = "Timeout in ms";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "DetectorConfigFiles";
	prop_desc = "Define the list of Detector Configuration files files and their associated alias.";
	prop_def  = "ALIAS;PATH_AND_FILE_NAME";
	vect_data.clear();
	vect_data.push_back("ALIAS;PATH_AND_FILE_NAME");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedThresholdLow";
	prop_desc = "Only the device could modify this property <br>\nThe User should never change this property<br>";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedThresholdHigh";
	prop_desc = "Only the device could modify this property <br>\nThe User should never change this property<br>";
	prop_def  = "0";
	vect_data.clear();
	vect_data.push_back("0");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedConfigAlias";
	prop_desc = "Only the device could modify this property <br>\nThe User should never change this property<br>";
	prop_def  = "ALIAS";
	vect_data.clear();
	vect_data.push_back("ALIAS");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

	prop_name = "MemorizedTriggerAcquisitionFrequency";
	prop_desc = "Only the device could modify this property <br>\nThe User should never change this property<br>";
	prop_def  = "1";
	vect_data.clear();
	vect_data.push_back("1");
	if (prop_def.length()>0)
	{
		Tango::DbDatum	data(prop_name);
		data << vect_data ;
		dev_def_prop.push_back(data);
		add_wiz_dev_prop(prop_name, prop_desc,  prop_def);
	}
	else
		add_wiz_dev_prop(prop_name, prop_desc);

}
//+----------------------------------------------------------------------------
//
// method : 		UfxcClass::write_class_property
// 
// description : 	Set class description as property in database
//
//-----------------------------------------------------------------------------
void UfxcClass::write_class_property()
{
	//	First time, check if database used
	//--------------------------------------------
	if (Tango::Util::_UseDb == false)
		return;

	Tango::DbData	data;
	string	classname = get_name();
	string	header;
	string::size_type	start, end;

	//	Put title
	Tango::DbDatum	title("ProjectTitle");
	string	str_title("Device specific for Ufxc detector");
	title << str_title;
	data.push_back(title);

	//	Put Description
	Tango::DbDatum	description("Description");
	vector<string>	str_desc;
	str_desc.push_back("  ");
	description << str_desc;
	data.push_back(description);
		
	//	put cvs or svn location
	string	filename(classname);
	filename += "Class.cpp";
	
	// Create a string with the class ID to
	// get the string into the binary
	string	class_id(ClassId);
	
	// check for cvs information
	string	src_path(CvsPath);
	start = src_path.find("/");
	if (start!=string::npos)
	{
		end   = src_path.find(filename);
		if (end>start)
		{
			string	strloc = src_path.substr(start, end-start);
			//	Check if specific repository
			start = strloc.find("/cvsroot/");
			if (start!=string::npos && start>0)
			{
				string	repository = strloc.substr(0, start);
				if (repository.find("/segfs/")!=string::npos)
					strloc = "ESRF:" + strloc.substr(start, strloc.length()-start);
			}
			Tango::DbDatum	cvs_loc("cvs_location");
			cvs_loc << strloc;
			data.push_back(cvs_loc);
		}
	}
	// check for svn information
	else
	{
		string	src_path(SvnPath);
		start = src_path.find("://");
		if (start!=string::npos)
		{
			end = src_path.find(filename);
			if (end>start)
			{
				header = "$HeadURL: ";
				start = header.length();
				string	strloc = src_path.substr(start, (end-start));
				
				Tango::DbDatum	svn_loc("svn_location");
				svn_loc << strloc;
				data.push_back(svn_loc);
			}
		}
	}

	//	Get CVS or SVN revision tag
	
	// CVS tag
	string	tagname(TagName);
	header = "$Name: ";
	start = header.length();
	string	endstr(" $");
	
	end   = tagname.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strtag = tagname.substr(start, end-start);
		Tango::DbDatum	cvs_tag("cvs_tag");
		cvs_tag << strtag;
		data.push_back(cvs_tag);
	}
	
	// SVN tag
	string	svnpath(SvnPath);
	header = "$HeadURL: ";
	start = header.length();
	
	end   = svnpath.find(endstr);
	if (end!=string::npos && end>start)
	{
		string	strloc = svnpath.substr(start, end-start);
		
		string tagstr ("/tags/");
		start = strloc.find(tagstr);
		if ( start!=string::npos )
		{
			start = start + tagstr.length();
			end   = strloc.find(filename);
			string	strtag = strloc.substr(start, end-start-1);
			
			Tango::DbDatum	svn_tag("svn_tag");
			svn_tag << strtag;
			data.push_back(svn_tag);
		}
	}

	//	Get URL location
	string	httpServ(HttpServer);
	if (httpServ.length()>0)
	{
		Tango::DbDatum	db_doc_url("doc_url");
		db_doc_url << httpServ;
		data.push_back(db_doc_url);
	}

	//  Put inheritance
	Tango::DbDatum	inher_datum("InheritedFrom");
	vector<string> inheritance;
	inheritance.push_back("Device_4Impl");
	inher_datum << inheritance;
	data.push_back(inher_datum);

	//	Call database and and values
	//--------------------------------------------
	get_db_class()->put_property(data);
}

}	// namespace