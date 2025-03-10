//=============================================================================
//
// file :        Pco.h
//
// description : Include for the Pco class.
//
// project :	Device specific for Pco detector
//
// $Author:  $
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
//		 BP48 - 91192 Gif sur Yvette
//               FRANCE
//
//=============================================================================
//
//  		This file is generated by POGO
//	(Program Obviously used to Generate tango Object)
//
//         (c) - Software Engineering Group - ESRF
//=============================================================================
#ifndef _PCO_H
#define _PCO_H

#include "tango.h"
#include "Factory.h"

#include "lima/HwInterface.h"
#include "lima/CtControl.h"
#include "lima/CtAcquisition.h"
#include "lima/CtImage.h"
#include <PcoInterface.h>

// YAT / 4Tango
#include <yat/utils/String.h>
#include <yat/utils/StringTokenizer.h>
#include <yat/utils/Logging.h>
#include <yat4tango/PropertyHelper.h>
#include <yat4tango/ExceptionHelper.h>
#include <yat4tango/DynamicInterfaceManager.h>

/**
 * @author	$Author:  $
 * @version	$Revision:  $
 */

//	Add your own constant definitions here.
//-----------------------------------------------

#define MAX_ATTRIBUTE_STRING_LENGTH     256
const bool  NOT_MEMORIZED               = false;
const bool  NOT_WRITE_MEMORIZED_AT_INIT = false;
const bool  MEMORIZED                   = true;
const bool  WRITE_MEMORIZED_AT_INIT     = true;



namespace Pco_ns
{

    /**
     * Class Description:
     * 
 */

/*
 *	Device States Description:
*  Tango::INIT :
*  Tango::STANDBY :
*  Tango::FAULT :
*  Tango::RUNNING :
 */


    class Pco : public Tango::Device_4Impl
    {
    public:
        //	Add your own data members here
        //-----------------------------------------
        //- Used for dynamic attributes
        Tango::DevULong     *attr_maxNbImage_read;
        Tango::DevBoolean   *attr_cdiMode_read;
        Tango::DevBoolean   attr_cdiMode_write;
        Tango::DevDouble    *attr_frameRate_read;
        Tango::DevShort    *attr_coolingSetPoint_read;
        Tango::DevShort    attr_coolingSetPoint_write;
        Tango::DevString    *attr_adcOperation_read;
        Tango::DevString    attr_adcOperation_write;
        Tango::DevString    *attr_shutterMode_read;
        Tango::DevString    attr_shutterMode_write;

        //	Here is the Start of the automatic code generation part
        //-------------------------------------------------------------	
        /**
         *	@name attributes
         *	Attribute member data.
         */
        //@{
		Tango::DevString	*attr_pixelRate_read;
		Tango::DevString	attr_pixelRate_write;
		Tango::DevBoolean	*attr_doubleImage_read;
		Tango::DevBoolean	attr_doubleImage_write;
		Tango::DevULong	*attr_currentRecordedFrame_read;
		Tango::DevString	*attr_cameraModel_read;
		Tango::DevFloat	*attr_sensorTemperature_read;
		Tango::DevBoolean	*attr_forcedFIFOMode_read;
		Tango::DevBoolean	attr_forcedFIFOMode_write;
		Tango::DevString	*attr_dllVersion_read;
//@}

        /**
         * @name Device properties
         * Device properties member data.
         */
        //@{
/**
 *	Serial Number of the camera: used to select camera if several connected to the same host
 */
	string	serialNumber;
//@}

        /**
         *	@name Device properties
         *	Device property member data.
         */
        //@{
        //@}

        /**@name Constructors
         * Miscellaneous constructors */
        //@{
        /**
         * Constructs a newly allocated Command object.
         *
         *	@param cl	Class.
         *	@param s 	Device Name
         */
        Pco(Tango::DeviceClass *cl, string &s);
        /**
         * Constructs a newly allocated Command object.
         *
         *	@param cl	Class.
         *	@param s 	Device Name
         */
        Pco(Tango::DeviceClass *cl, const char *s);
        /**
         * Constructs a newly allocated Command object.
         *
         *	@param cl	Class.
         *	@param s 	Device name
         *	@param d	Device description.
         */
        Pco(Tango::DeviceClass *cl, const char *s, const char *d);
        //@}

        /**@name Destructor
         * Only one destructor is defined for this class */
        //@{

                /**
         * The object destructor.
         */
        ~Pco()
        {
            delete_device();
        };
        /**
         *	will be called at device destruction or at init command.
         */
        void delete_device();
        //@}


        /**@name Miscellaneous methods */
        //@{
        /**
         *	Initialize the device
         */
        virtual void init_device();
        /**
         *	Always executed method before execution command method.
         */
        virtual void always_executed_hook();

//@}

/**
 * @name Pco methods prototypes
 */

//@{
/**
 *	Hardware acquisition for attributes.
 */
	virtual void read_attr_hardware(vector<long> &attr_list);
/**
 *	Extract real attribute values for pixelRate acquisition result.
 */
	virtual void read_pixelRate(Tango::Attribute &attr);
/**
 *	Write pixelRate attribute values to hardware.
 */
	virtual void write_pixelRate(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for doubleImage acquisition result.
 */
	virtual void read_doubleImage(Tango::Attribute &attr);
/**
 *	Write doubleImage attribute values to hardware.
 */
	virtual void write_doubleImage(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for currentRecordedFrame acquisition result.
 */
	virtual void read_currentRecordedFrame(Tango::Attribute &attr);
/**
 *	Extract real attribute values for cameraModel acquisition result.
 */
	virtual void read_cameraModel(Tango::Attribute &attr);
/**
 *	Extract real attribute values for sensorTemperature acquisition result.
 */
	virtual void read_sensorTemperature(Tango::Attribute &attr);
/**
 *	Extract real attribute values for forcedFIFOMode acquisition result.
 */
	virtual void read_forcedFIFOMode(Tango::Attribute &attr);
/**
 *	Write forcedFIFOMode attribute values to hardware.
 */
	virtual void write_forcedFIFOMode(Tango::WAttribute &attr);
/**
 *	Extract real attribute values for dllVersion acquisition result.
 */
	virtual void read_dllVersion(Tango::Attribute &attr);
/**
 *	Read/Write allowed for pixelRate attribute.
 */
	virtual bool is_pixelRate_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for doubleImage attribute.
 */
	virtual bool is_doubleImage_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for currentRecordedFrame attribute.
 */
	virtual bool is_currentRecordedFrame_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for cameraModel attribute.
 */
	virtual bool is_cameraModel_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for sensorTemperature attribute.
 */
	virtual bool is_sensorTemperature_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for forcedFIFOMode attribute.
 */
	virtual bool is_forcedFIFOMode_allowed(Tango::AttReqType type);
/**
 *	Read/Write allowed for dllVersion attribute.
 */
	virtual bool is_dllVersion_allowed(Tango::AttReqType type);
/**
 *	Execution allowed for Talk command.
 */
	virtual bool is_Talk_allowed(const CORBA::Any &any);
/**
 *	Execution allowed for GetCamInfo command.
 */
	virtual bool is_GetCamInfo_allowed(const CORBA::Any &any);
/**
 * This command gets the device state (stored in its <i>device_state</i> data member) and returns it to the caller.
 *	@return	State Code
 *	@exception DevFailed
 */
	virtual Tango::DevState	dev_state();
/**
 * Availables values are:<br>
 *	lasterror<br>
 *	camInfo<br>
 *	camType<br>
 *	clTransferParam<br>
 *	cocRunTime<br>
 *	frameRate<br>
 *	maxNbImages<br>
 *	timestamp<br>
 *	" "<br>
 *	@param	argin	str argin
 *	@return	str argout
 *	@exception DevFailed
 */
	Tango::DevString	talk(Tango::DevString);
/**
 * Get Camera Infos
 *	@return	cam infos
 *	@exception DevFailed
 */
	Tango::DevString	get_cam_info();

/**
 *	Read the device properties from database
 */
	 void get_device_property();
//@}

        //	Here is the end of the automatic code generation part
        //-------------------------------------------------------------	


    protected:
        //	Add your own data members here
        //-----------------------------------------

        std::string m_camera_model, m_dll_version;

        ///generic method to create a tango dynamic attribute
        void create_dynamic_interface();
        template <class F1, class F2>
        void create_attribute(std::string name,
            int data_type,
            Tango::AttrDataFormat data_format,
            Tango::AttrWriteType access_type,
            Tango::DispLevel disp_level,
            const std::string& unit,
            const std::string& format,
            const std::string& desc,
            const std::string& label,
            /*bool memorized,
            bool write_memorized_value_at_init,*/
            F1 read_callback,
            F2 write_callback);

        //- maxNbImage
        void read_maxNbImage_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        //- cdi
        void read_cdiMode_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        void write_cdiMode_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
        //bool is_cdiMode_allowed(Tango::AttReqType type);
        //- frameRate
        void read_frameRate_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        //- coolingSetPoint
        void read_coolingSetPoint_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        void write_coolingSetPoint_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
        //- adcOperation
        void read_adcOperation_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        void write_adcOperation_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);
        //- shutterMode
        void read_shutterMode_callback(yat4tango::DynamicAttributeReadCallbackData& cbd);
        void write_shutterMode_callback(yat4tango::DynamicAttributeWriteCallbackData& cbd);        
        // method for tango dyn attributes WHEN no write part is available - NULL
        void write_callback_null(yat4tango::DynamicAttributeWriteCallbackData& cbd){/*nop*/}
        
        //state & status stuff
        // return true if the device is correctly initialized in init_device
        bool                    is_device_initialized() {return m_is_device_initialized;};
        bool                    m_is_device_initialized;
        stringstream            m_status_message;
        //lima OBJECTS
        lima::Pco::Interface*   m_hw;
        lima::CtControl*        m_ct;
        lima::Pco::Camera*      m_camera;

        std::string             m_pixel_scan_rate; //pixel scan rate 	(SLOW, FAST)
        std::string             m_shutter_mode; //shutter mode name 	(GLOBAL, ROLLING)
        Tango::DevString        m_dev_string_val;
        map<string, long>       m_map_scan_rate_frequencies;

        //- yat4tango Dynamic Interface Manager
        yat4tango::DynamicInterfaceManager m_dim;
    };

} // namespace_ns

///////////////////////////////////////////////////////////////////////////////
//// INCLUDE TEMPLATE IMPLEMENTAION
///////////////////////////////////////////////////////////////////////////////    
#include "Pco.hpp"

#endif	// _PCO_H
