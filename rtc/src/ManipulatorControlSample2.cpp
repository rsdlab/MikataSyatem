// -*- C++ -*-
// <rtc-template block="description">
/*!
 * @file  ManipulatorControlSample2.cpp
 * @brief ModuleDescription
 *
 */
// </rtc-template>

#include "ManipulatorControlSample2.h"

int globalK=0;

// Module specification
// <rtc-template block="module_spec">
#if RTM_MAJOR_VERSION >= 2
static const char* const manipulatorcontrolsample2_spec[] =
#else
static const char* manipulatorcontrolsample2_spec[] =
#endif
  {
    "implementation_id", "ManipulatorControlSample2",
    "type_name",         "ManipulatorControlSample2",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "VenderName",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    // Configuration variables
    "conf.default.Speed", "20",

    // Widget
    "conf.__widget__.Speed", "text",
    // Constraints

    "conf.__type__.Speed", "int",

    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ManipulatorControlSample2::ManipulatorControlSample2(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_ManipulatorCommonInterface_CommonPort("ManipulatorCommonInterface_Common"),
    m_ManipulatorCommonInterface_MiddlePort("ManipulatorCommonInterface_Middle")
    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
ManipulatorControlSample2::~ManipulatorControlSample2()
{
}



RTC::ReturnCode_t ManipulatorControlSample2::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  
  // Set OutPort buffer

  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  m_ManipulatorCommonInterface_CommonPort.registerConsumer("JARA_ARM_ManipulatorCommonInterface_Common", "JARA_ARM::ManipulatorCommonInterface_Common", m_JARA_ARM_ManipulatorCommonInterface_Common);
  m_ManipulatorCommonInterface_MiddlePort.registerConsumer("JARA_ARM_ManipulatorCommonInterface_Middle", "JARA_ARM::ManipulatorCommonInterface_Middle", m_JARA_ARM_ManipulatorCommonInterface_Middle);
  
  // Set CORBA Service Ports
  addPort(m_ManipulatorCommonInterface_CommonPort);
  addPort(m_ManipulatorCommonInterface_MiddlePort);
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("Speed", m_Speed, "20");
  // </rtc-template>

  
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorControlSample2::onActivated(RTC::UniqueId ec_id)
{
  globalK=1;
  /*
  std::cout << "Activate OK!" << std::endl;
  m_JARA_ARM_ManipulatorCommonInterface_Common->servoON();
  JARA_ARM::JointPos jointPoint;
  jointPoint.length(6);
  std::cout << "Activate OK!" << std::endl;

  jointPoint[0]=0;
  jointPoint[1]=0;
  jointPoint[2]=0;
  jointPoint[3]=0;
  jointPoint[4]=0;
  jointPoint[5]=0;
  m_JARA_ARM_ManipulatorCommonInterface_Middle->movePTPJointAbs(jointPoint);
  std::cout << "Activate OK!" << std::endl;
  */
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorControlSample2::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t ManipulatorControlSample2::onExecute(RTC::UniqueId ec_id) 
{
  //std::cout << "Activate OK!" << std::endl;
  //globalK==1
  //std::cout << globalK << std::endl;
  if(globalK==1)
  {
    m_JARA_ARM_ManipulatorCommonInterface_Common->servoON();
    JARA_ARM::JointPos jointPoint;
    jointPoint.length(6);
    std::cout << "Activate OK!" << std::endl;

    jointPoint[0]=0;
    jointPoint[1]=0;
    jointPoint[2]=0;
    jointPoint[3]=0;
    jointPoint[4]=0;
    jointPoint[5]=0;
    m_JARA_ARM_ManipulatorCommonInterface_Middle->movePTPJointAbs(jointPoint);
    std::cout << "Activate OK!" << std::endl;
    globalK=0;
  }
 
 int c;

  std::cout << "コマンドを選択してください" << std::endl;
  std::cout << "1 : アーム関節角度" << std::endl;
  std::cout << "2 : アーム先端座標" << std::endl;
  std::cout << "3 : 終了" << std::endl;


  std::cout << ">>";
  std::cin >> c; 
  std::cout << std::endl; 

  //アーム関節角度
  if(c == 1)
    {
      m_JARA_ARM_ManipulatorCommonInterface_Common->servoON();
      JARA_ARM::JointPos jointPoint;
      jointPoint.length(6);
      std::cout << "土台から先端に向かって第1関節〜第6関節" << std::endl << "関節角度を入力してください　単位[rad]" << std::endl;
      std::cout << "第1関節の角度 : ";
      std::cin >>jointPoint[0];
      std::cout << "第2関節の角度 : ";
      std::cin >>jointPoint[1];
      std::cout << "第3関節の角度 : ";
      std::cin >>jointPoint[2];
      std::cout << "第4関節の角度 : ";
      std::cin >>jointPoint[3];
      std::cout << "第5関節の角度 : ";
      std::cin >>jointPoint[4];
      std::cout << "第6関節の角度 : ";
      std::cin >>jointPoint[5];
      std::cout << std::endl; 
      
      m_JARA_ARM_ManipulatorCommonInterface_Middle->movePTPJointAbs(jointPoint);
    }
  //アーム先端座標
  else if(c == 2)
    {
      m_JARA_ARM_ManipulatorCommonInterface_Common->servoON();
      float x;
      float y;
      float z;
      JARA_ARM::CarPosWithElbow pos;
      
      std::cout << "座標を入力してください　単位[mm]" << std::endl;
      std::cout << "x座標 : "; 
      std::cin >> x;
      std::cout << "y座標 : ";
      std::cin >> y;
      std::cout << "z座標 : ";
      std::cin >> z;
      std::cout << std::endl; 

      //[mm]-->[m]
      x = x/1000;
      y = y/1000;
      z = z/1000;
      
      pos.carPos[0][3] = x;
      pos.carPos[1][3] = y;
      pos.carPos[2][3] = z;
      
      m_JARA_ARM_ManipulatorCommonInterface_Middle->movePTPCartesianAbs(pos);
    }
  //終了
  else if(c == 3)
    {
      std::cout << "END" << std::endl;
      std::cout << "システムをDeactivateしてください" << std::endl<<std::endl;
      deactivate(ec_id);
    }
  
  else 
    std::cout << "無効な値です" << std::endl<<std::endl;

  
  
  return RTC::RTC_OK;
}




extern "C"
{
 
  void ManipulatorControlSample2Init(RTC::Manager* manager)
  {
    coil::Properties profile(manipulatorcontrolsample2_spec);
    manager->registerFactory(profile,
                             RTC::Create<ManipulatorControlSample2>,
                             RTC::Delete<ManipulatorControlSample2>);
  }
  
}
