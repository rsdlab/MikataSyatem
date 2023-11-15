/***************************************************
 * Dynamixel.h
 *
 * created 2010/04/20
 * author Yuki Suga (SUGAR SWEET ROBOTICS)
 * email  ysuga@ysuga.net
 * copyright SUGAR SWEET ROBOTICS
 ***************************************************/

#pragma once

#ifdef WIN32
// �ȉ��� ifdef �u���b�N�� DLL ����̃G�N�X�|�[�g��e�Ղɂ���}�N�����쐬���邽�߂� 
// ��ʓI�ȕ��@�ł��B���� DLL ���̂��ׂẴt�@�C���́A�R�}���h ���C���Œ�`���ꂽ LIBARM_EXPORTS
// �V���{���ŃR���p�C������܂��B���̃V���{���́A���� DLL ���g���v���W�F�N�g�Œ�`���邱�Ƃ͂ł��܂���B
// �\�[�X�t�@�C�������̃t�@�C�����܂�ł��鑼�̃v���W�F�N�g�́A 
// LIBDXL_API �֐��� DLL ����C���|�[�g���ꂽ�ƌ��Ȃ��̂ɑ΂��A���� DLL �́A���̃}�N���Œ�`���ꂽ
// �V���{�����G�N�X�|�[�g���ꂽ�ƌ��Ȃ��܂��B
#ifdef dynamixel_EXPORTS
#define LIBDXL_API __declspec(dllexport)
#else
#define LIBDXL_API __declspec(dllimport)
#endif

#else // ifdef WIN32
#define LIBDXL_API 

#endif // ifdef WIN32

#include "Exception.h"

#include "SerialPort.h"
#include "Thread.h"

namespace ssr {
  namespace dynamixel {

    /** 
     * @if jp
     * @brief Dynamixel���[�^�̓�������Ɏg���\����
     *
     * @else
     *
     * @brief Struct used when synchronized motor motion
     *
     * @endif
     * @author Yuki Suga, Hirotaka Hachiya (Revast Co., Ltd.)
     * @see CDynamixel#SendSyncPosition(SyncPosData*, int)
     */
    struct LIBDXL_API SyncPosData{
      /**
       * @if jp
       * @brief Dynamixel���[�^��ID�ԍ�
       * @else
       * @endif
       */
      uint8_t  ID;
      /**
       * @if jp
       * @brief Dynamixel���[�^�̖ڕW�ʒu
       * @else
       * @endif
       */
      uint16_t GoalPosition;
    };
    
    /** 
     * @if jp
     * @brief Dynamixel���[�^�̐���N���X
     *
     * �V���A���|�[�g�N���X�ł���CSerialPort���p�����Ă���B
     * �ЂƂ̃V���A���o�X�ɂ��ADynamixel�N���X���ЂƂK�v�Ƃ���B
     *
     * @else
     * @brief Dynamixel RC Servo Motor Controlling Class.
     *
     * @endif
     * @author Yuki Suga (Revast Co., Ltd.)
     * @see CSerialPort
     */
    class LIBDXL_API Dynamixel {
    private:
      ssr::SerialPort m_SerialPort;
      ssr::Mutex m_Mutex;
      ssr::Timer m_Timer;
      
      // Instruction
      enum TInstruction{
	INST_PING=1,
	INST_READ=2,
	INST_WRITE=3,
	INST_REG_WRITE=4,
	INST_ACTION=5,
	INST_RESET=6,
	INST_SYNC_WRITE=0x83,
	INST_SYNG_REG_WRITE=0x85
      } ;
      
      static const int32_t PACKET_HEADER_SIZE = 4;
      static const uint8_t PACKET_HEADER_FIXED_VALUE0 = 0xFFU;
      static const uint8_t PACKET_HEADER_FIXED_VALUE1 = 0xFFU;
      static const uint8_t PACKET_MAX_ID = 254U;
      static const uint8_t PACKET_MAX_DATASIZE = 120U;
      static const int32_t DYNAMIXEL_RECEIVEPACKET_TRYCYCLE = 10;
      
    private:
      
      
    public:
      /**
       * @if jp
       * @brief ���͓d���͈͊O�G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t INPUT_VOLTAGE_ERROR_FLAG = 0x01;
      
      /**
       * @if jp
       * @brief �p�x���ߔ͈͊O�G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t ANGLE_LIMIT_ERROR_FLAG = 0x02;
      
      /**
       * @if jp
       * @brief ���[�^���x�͈͊O�G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t OVERHEATING_ERROR_FLAG = 0x04;
      
      /**
       * @if jp
       * @brief �ݒ�l�͈͊O�G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t RANGE_ERROR_FLAG = 0x08;
      
      /**
       * @if jp
       * @brief �ʐM�p�P�b�g�`�F�b�N�T���G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t CHECKSUM_ERROR_FLAG = 0x10;
      
      /**
       * @if jp
       * @brief �ߕ��׃G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t OVERLOAD_ERROR_FLAG = 0x20;
      
      /**
       * @if jp
       * @brief �s���Ȗ��߂ŋN����G���[�t���O
       * @endif
       * @see #SetAlarmShutdownFlag
       * @see #SetAlarmLEDFlag
       * @see #GetAlarmShutdownFlag
       * @see #GetAlarmLEDFlag
       */
      static const uint8_t INSTRUCTION_ERROR_FLAG = 0x40;
      
      /** 
       * @if jp
       * @brief �f�t�H���g�̑҂����ԁB����ȏ�҂ꍇ��CTimeOutException���X���[�����B
       *
       * @else
       * @brief Default Timeout value. [ms]
       * 
       * @endif
       * @see CTimeOutException
       *
       */
      static const int32_t DEFAULT_RESPONSE_TIME = 50;
      
      /** 
       * @if jp
       * @brief �u���[�h�L���X�e�B���OID
       *
       * ���ׂẴ��[�^�ɓ����ɖ��߂𑗂�ꍇ��ID�ԍ��B�u���[�h�L���X�g�p�P�b�g�𑗐M�����ꍇ�́A���[�^����X�e�[�^�X�p�P�b�g���Ԃ�Ȃ��B
       *
       * @else
       *
       * @brief Broadcast ID used when all servo receive commands.
       * @endif
       *
       */
      static const uint8_t BROADCASTING_ID = 254U;

    public:
      /** 
       * @if jp
       * @brief �R���X�g���N�^
       *
       * @param com_prot COM�|�[�g��
       * @param baudrate �{�[���[�g�B�ʐM���x�B�f�t�H���g��54713�B
       *
       * @else
       *
       * @brief Constructor
       * @param com_port Serial port file name.
       * @param baudrate baudrate.
       * @endif
       *
       * @exception CComOpenException
       * @exception CComStateException
       */
      Dynamixel(const char* com_port, const long baudrate=54713);
	
      /** 
       * @if jp
       * @brief �f�X�g���N�^
       *
       * @else
       *
       * @brief Destructor
       * @endif
       *
       */
      virtual ~Dynamixel(void);
		
    private:
      /** 
       * @if jp
       * @brief COM�|�[�g�Ƀp�P�b�g���M
       *
       * @else
       *
       * @brief Write data packet to COM port.
       * @param cID ID number of RC servo.
       * @param cInst instruction code.
       * @param pParam data value.
       * @param iLength length of packet.
       * @endif
       *
       * @exception CComAccessException
       * @exception CWritePacketException
       */
      void WritePacket (uint8_t cID, 
			TInstruction cInst, 
			uint8_t *pParam, 
			int32_t iLength);

      /** 
       * @if jp
       * @brief COM�|�[�g����p�P�b�g��M
       *
       * @else
       *
       * @brief Receive data packet to COM port.
       * @param pRcv pointer to received data buffer.
       * @param pLength length of packet.
       * @param timeout timeout value.
       * @endif
       *
       * @exception CComAccessException
       * @exception CReceivePacketException
       * @exception CTimeOutException
       * @exception CAngleLimitException
       * @exception CChecksumException
       * @exception CInputVoltageException
       * @exception CInstructionException
       * @exception COverheatingException
       * @exception COverloadException
       * @exception CRangeException
       */
      void ReceivePacket (uint8_t *pRcv,
			  int32_t *pLength,
			  int32_t mask,
			  int32_t timeout);
		
			
      /** 
       * @if jp
       * @brief
       *
       * @else
       *
       * @brief Write data packet to COM port.
       * @param id ID number of RC servo.
       * @param adr address value.
       * @param dat data value.
       * @param timeout timeout value.
       * @endif
       *
       * @exception revast::system::CComAccessException
       * @exception revast::dynamixel::ReceivePacketException
       * @exception revast::dynamixel::WritePacketException
       * @exception revast::dynamixel::TimeOutException
       * @exception revast::dynamixel::AngleLimitException
       * @exception revast::dynamixel::ChecksumException
       * @exception revast::dynamixel::InputVoltageException
       * @exception revast::dynamixel::InstructionException
       * @exception revast::dynamixel::OverheatingException
       * @exception revast::dynamixel::OverloadException
       * @exception revast::dynamixel::RangeException
       */
      void WriteByteData (uint8_t id,
			  uint8_t adr, 
			  uint8_t dat, 
			  int32_t mask,
			  int32_t timeout);

      /** 
       * @if jp
       * @brief
       *
       * @else
       *
       * @brief Write data packet to COM port.
       * @param id ID number of RC servo.
       * @param adr address value.
       * @param dat data value.
       * @param timeout timeout value.
       * @endif
       *
       * @exception revast::system::CComAccessException
       * @exception revast::dynamixel::ReceivePacketException
       * @exception revast::dynamixel::WritePacketException
       * @exception revast::dynamixel::TimeOutException
       * @exception revast::dynamixel::AngleLimitException
       * @exception revast::dynamixel::ChecksumException
       * @exception revast::dynamixel::InputVoltageException
       * @exception revast::dynamixel::InstructionException
       * @exception revast::dynamixel::OverheatingException
       * @exception revast::dynamixel::OverloadException
       * @exception revast::dynamixel::RangeException
       */
      void ReadByteData (uint8_t id,
			 uint8_t adr, 
			 uint8_t *result,
			 int32_t mask,
			 int32_t timeout);

      /** 
       * @if jp
       * @brief
       *
       * @else
       *
       * @brief Write data packet to COM port.
       * @param id ID number of RC servo.
       * @param adr address value.
       * @param dat data value.
       * @param timeout timeout value.
       * @endif
       *
       * @exception revast::system::CComAccessException
       * @exception revast::dynamixel::ReceivePacketException
       * @exception revast::dynamixel::WritePacketException
       * @exception revast::dynamixel::TimeOutException
       * @exception revast::dynamixel::AngleLimitException
       * @exception revast::dynamixel::ChecksumException
       * @exception revast::dynamixel::InputVoltageException
       * @exception revast::dynamixel::InstructionException
       * @exception revast::dynamixel::OverheatingException
       * @exception revast::dynamixel::OverloadException
       * @exception revast::dynamixel::RangeException
       */
      void WriteWordData (uint8_t id,
			  uint8_t adr,
			  uint16_t dat, 
			  int32_t mask,
			  int32_t timeout);

      /** 
       * @if jp
       * @brief
       *
       * @else
       *
       * @brief Read data packet from COM port.
       * @param id ID number of RC servo.
       * @param adr address value.
       * @param result data value buffer.
       * @param timeout timeout value.
       * @endif
       *
       * @exception revast::system::CComAccessException
       * @exception revast::dynamixel::ReceivePacketException
       * @exception revast::dynamixel::WritePacketException
       * @exception revast::dynamixel::TimeOutException
       * @exception revast::dynamixel::AngleLimitException
       * @exception revast::dynamixel::ChecksumException
       * @exception revast::dynamixel::InputVoltageException
       * @exception revast::dynamixel::InstructionException
       * @exception revast::dynamixel::OverheatingException
       * @exception revast::dynamixel::OverloadException
       * @exception revast::dynamixel::RangeException
       */
      void ReadWordData (uint8_t id, 
			 uint8_t adr, 
			 uint16_t *result,
			 int32_t mask, 
			 int32_t timeout );

    public:

      /** 
       * @if jp
       * @brief �T�[�{��ON/OFF���܂��B
       *
       * ���[�^�ɂ�����g���N��ON/OFF�𐧌䂵�܂��B 
       *
       * @param id ���[�^��ID�ԍ�
       * @param on �g���N��ON/OFF�t���O�BTRUE�Ȃ�΃g���NON�BFALSE�Ȃ�΃g���NOFF�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set Compliant mode 
       *
       * When this function is called, the motor is off. <BR />
       * CAUTION!!!! <BR />
       * When the motor is off, the joint32_t of robot is free.
       * If the robot fall down onto the floor, that might destroy the robot. 
       *
       * @param id RC servo id.
       * @param on flag. if TRUE, servo will be compliant (free). else, servo will be on (rigid).
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetCompliant (uint8_t id, bool on, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ID�ԍ��Ȃǂ̕ύX�����b�N���܂��B
       *
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @else
       *
       * @brief Lock ID number of servo motor. 
       *
       * <BR />
       * After calling this function, the ID of motor cannot be modified.
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void LockItem (int32_t mask=0x7F);

      /** 
       * @if jp
       * @brief �ڕW�ʒu���������݂܂��B
       * @param id ���[�^��ID�ԍ�
       * @param position ���[�^�̖ڕW�ʒu�B[0, 1023]�ŁA�T�[�{�z�[���́}75�x�ɑΉ��B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Send target position to the servo motor.
       * 
       * @param id ID number of RC servo.
       * @param position target position. [0-1023]
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void MovePosition (uint8_t id, uint16_t position, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);


      /** 
       * @if jp
       * @brief ���݂̃��[�^�̃��f���ԍ����擾�B
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���[�^�̃��f���ԍ��B
       *
       * @else
       *
       * @brief Get target position of RC servo motor.
       * 
       * @param id ID number of RC servo.
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout timeout value.
       * @return model number
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetModelNumber (uint8_t id, int32_t mask=0x7F,
				     int32_t timeout = DEFAULT_RESPONSE_TIME) ;



      /** 
       * @if jp
       * @brief ���݂̃��[�^�̈ʒu���擾�B
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݈ʒu�B[0, 1023]�̒l���A�}75�x�ɑΉ��B
       *
       * @else
       *
       * @brief Get target position of RC servo motor.
       * 
       * @param id ID number of RC servo.
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout timeout value.
       * @return target position [0-1023]
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetCurrentPosition (uint8_t id,
					 int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME) ;

      /** 
       * @if jp
       * @brief ���݂̖ڕW�ʒu���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݂̖ڕW�ʒu�B[0, 1023]���}75�x�ɑΉ�
       * 
       * @else
       *
       * @brief Get target position of RC servo motor.
       * 
       * @param id ID number of RC servo.
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout timeout value.
       * @return target position [0-1023]
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetTargetPosition (uint8_t id,
					int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���݂̖ڕW���x���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param velocity ���݂̖ڕW���x�B[0-1023]�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Send target velocity to the servo motor.
       *
       * The velocity will be active when the MoveImmediately command is called next.
       * @param id ID number of RC servo.
       * @param velocity target velocity. [0-1023]
       * @endif
       *
       * @see #MoveImmediately(uint8_t, uint16_t)
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetTargetVelocity (uint8_t id,uint16_t velocity, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���݂̖ڕW���x���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @return ���݂̖ڕW���x�B[0-1023]�B
       * @else
       *
       * @brief Get target velocity.
       * @param id ID number of RC servo.
       * @param timeout timeout value.
       * @return target velocity [0-1023]
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetTargetVelocity (uint8_t id,
					int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���ݑ��x���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @return ���݂̉�]���x�B[0-1023]�B
       * @else
       * 
       * @brief Get current velocity. 
       * @param id ID number of RC servo.
       * @param timeout timeout value.
       * @return current velocity [-1023, +1023]
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      short GetCurrentVelocity(uint8_t id, int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME);


      // obsolute
      //void MoveVelocity (uint8_t id, uint16_t velocity);

      /** 
       * @if jp
       * @brief �g���N�����l�̐ݒ�B
       *
       * �g���N�����l�𒴂���g���N�̔�����}������BCOverloadException�́A���[�^�̋@�\���E�̏ꍇ�ɃX���[������O�Ȃ̂ŁA
       * ���̐ݒ�l�Ƃ͊֌W�Ȃ��B
       * @param id ���[�^��ID�ԍ�
       * @param torque �g���N�̐����l�B[0, 1023]�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Send torque limitation value to the servo motor.
       * 
       * @param id ID number of RC servo.
       * @param torque torque limit. [0, 1023]. 0 = free. 1023 = maximum.
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetTorqueLimit (uint8_t id, uint16_t torque, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���݂̕��׃g���N�l���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @return ���݂̃g���N�B
       * @else
       *
       * @brief Get Current Torque.
       * @param id ID number of RC servo.
       * @return current torque (-1023, +1023).
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      short GetCurrentTorque(uint8_t id, int32_t mask=0x7F,  int32_t timeout = DEFAULT_RESPONSE_TIME);


      /** 
       * @if jp
       * @brief ���݂̃��[�^���x���擾�B
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݂̉��x�B�P�ʂ͓x�B
       * @else
       *
       * @brief Get Current Temperatur.
       * @param id ID number of RC servo.
       * @return current temperature (0, 1023).
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetCurrentTemperature(uint8_t id, int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���݂̃��[�^�ւ̋����d�����擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݂̋����d���l�B�P�ʂ�[V]�����A10�{�̒l���o�܂��B
       * @else
       *
       * @brief Get Supply Voltage.
       * @param id ID number of RC servo.
       * @return current supply Voltage (0, 26).
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetSupplyVoltage(uint8_t id, int32_t mask=0x7F, int32_t timeout = DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief LED�̓_���B
       *
       * @param id ���[�^��ID�ԍ�
       * @param flag LED�̓_��/�����B�f�t�H���g��TRUE�i�_���j�BFALSE��^����Ə����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set LED
       * @param id ID number of RC Servo.
       * @param flag if TRUE, LED is turned on. if FALSE, LED is turned off.
       * @endif
       *
       * @see #ClrLED(uint8_t, int)
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetLED(uint8_t id, int32_t flag = true,int32_t mask=0x7F,  int32_t timeout=DEFAULT_RESPONSE_TIME);


      /** 
       * @if jp
       * @brief LED�̏���
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Clear LED
       * @param id ID number of RC Servo.
       * @endif
       *
       * @see #SetLED(uint8_t, int, int)
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void ClearLED(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME) {
	SetLED(id, false, mask, timeout);
      }


      /** 
       * @if jp
       * @brief ���[�^�̓������䖽�߁B
       *
       * �ʏ�͉��L�̂悤�Ɏg���܂��B <BR />
       * ex:<BR />
       * > SyncPosData sp[2];<BR />
       * > sp[0].ID = 0;<BR />
       * > sp[0].GoalPosition = 100;<BR />
       * > sp[1].ID = 1;<BR />
       * > sp[1].GoalPosition = 100;<BR />
       * > SendSyncPosition(sp, 2); // move 2 motors synchronizingly.<BR />
       * 
       * @param pos �ڕW�f�[�^��ID�ԍ��̓�����SyncPosData�\���́B
       * @param num ���[�^�̌��B
       * @else
       *
       * @brief Send synchronizing motion packet.
       * ex:<BR />
       * > SyncPosData sp[2];<BR />
       * > sp[0].ID = 0;<BR />
       * > sp[0].GoalPosition = 100;<BR />
       * > sp[1].ID = 1;<BR />
       * > sp[1].GoalPosition = 100;<BR />
       * > SendSyncPosition(sp, 2); // move 2 motors synchronizingly.<BR />
       *
       * @param pos target data and id pair.
       * @param num the number of RC servo motor.
       * @endif
       * @see SyncPosData
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SendSyncPosition(SyncPosData *pos, int32_t num);


      /** 
       * @if jp
       * @brief CW��]�����̐����l�ݒ�
       *
       * @param id ���[�^��ID�ԍ�
       * @param position �����ʒu�B[0, 1023]�BCW < CCW�łȂ��Ă͂Ȃ�Ȃ��B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       * 
       * @brief Set CW Angle Limit Value
       * @param id ID of Motor
       * @param position Angle Limit (0-1023)
       * @endif
       *
       * @see ssr::dynamixel::AngleLimitException
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetCWAngleLimit(uint8_t id, uint16_t position, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME) ;

      /** 
       * @if jp
       * @brief CCW��]�����̐����l�ݒ�B
       *
       * @param id ���[�^��ID�ԍ�
       * @param position �����ʒu�B[0, 1023]�B CW < CCW�łȂ��Ă͂Ȃ�Ȃ��B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set CCW Angle Limit Value
       * @param id ID of Motor
       * @param position Angle Limit (0-1023)
       * @endif
       *
       * @see ssr::dynamixel::AngleLimitException
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetCCWAngleLimit(uint8_t id, uint16_t position, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME) ;
			
      /** 
       * @if jp
       * @brief ���[�^�̐����ʒu�擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݂̃��[�^��CW���������ʒu���擾�B[0, 1023]�B
       * @else
       *
       * @brief Get CW Angle Limit Value
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetCWAngleLimit(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���[�^��CCW���������ʒu���擾
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return ���݂̃��[�^��CCW���������ʒu���擾�B[0, 1023]
       * @else
       *
       * @brief Get CCW Angle Limit Value
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint16_t GetCCWAngleLimit(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���[�^��ID�ԍ��ύX
       *
       * @param id �ݒ��̃��[�^��ID�ԍ�
       * @param newID �V����ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetID(uint8_t id, uint8_t newID, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);


      /** 
       * @if jp
       * @brief ���[�^�̉��x���E�l�ݒ�
       *
       * ���̐ݒ�l�𒴂���� COverheatingException���X���[�����B
       *
       * @param id ���[�^��ID�ԍ�
       * @param temperature ���x���E�l�B�P�ʂ͓x�B�f�t�H���g��80�x�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see COverheatingException
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetHighestLimitTemperature(uint8_t id, uint8_t temperature, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);




      /** 
       * @if jp
       * @brief ���[�^�̒ʐM���x�ݒ�
       *
       * @param id ���[�^��ID�ԍ�
       * @param baudrate �ʐM���x�B�ʐM���x�� baudrate[bps] = 2000000 / (value + 1)�Ōv�Z�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetBaudRate(uint8_t id, uint8_t baudrate, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);


      /** 
       * @if jp
       * @brief ���[�^�̍Œዟ���d���ݒ�
       *
       * �Œዟ���d���������� CInputVoltageExceptin ���X���[�����B
       * @param id ���[�^��ID�ԍ�
       * @param voltage �Œዟ���d���B����������� CInputVoltageException���X���[�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see CInputVoltageException
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetLowestLimitVoltage(uint8_t id, uint8_t voltage, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief ���[�^�̍ő募���d���ݒ�
       *
       * �ő募���d���𒴂���� CInputVoltageExceptin ���X���[�����B
       * @param id ���[�^��ID�ԍ�
       * @param voltage �ő募���d���B����𒴂���� CInputVoltageException���X���[�����B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see CInputVoltageException
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetHighestLimitVoltage(uint8_t id, uint8_t voltage, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief �A���[�����������X�ꍇ�̎����g���N�I�t�ݒ�
       *
       * �Ή�����t���O��ON�ɂȂ��Ă���ƁA�G���[�����������ꍇ�Ƀg���N�I�t�ɂȂ�B
       * �f�t�H���g��0x24 ( Overload, Range Error )
       *
       * <BR />
       * ex: <BR />
       * >> SetAlarmShutdownFlag(0, OVERLOAD_ERROR_FLAG | RANGE_ERROR_FLAG | OVERHEATING_ERROR_FLAG);<BR />
       * >> // �ߕ��ׁA���x�͈͊O�Ɛݒ�l�͈͊O�̏ꍇ�Ɏ����I�Ƀg���N�I�t�B
       *
       * @param id ���[�^��ID�ԍ�
       * @param flag �G���[�t���O�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see INSTRUCTION_ERROR_FLAG
       * @see OVERLOAD_ERROR_FLAG
       * @see CHECKSUM_ERROR_FLAG
       * @see RANGE_ERROR_FLAG
       * @see OVERHEATING_ERROR_FLAG
       * @see ANGLE_LIMIT_ERROR_FLAG
       * @see INPUT_VOLTAGE_ERROR_FLAG
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetAlarmShutdownFlag(uint8_t id, uint8_t flag, int32_t mask=0x7F,  int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief �A���[�����������ꍇ�̎���LED�_���ݒ�
       *
       * �Ή�����t���O��ON�ɂȂ��Ă���ƁA�G���[�����������ꍇ��LED�_���B
       * �f�t�H���g��0x24 ( Overload, Range Error )
       *
       * <BR />
       * ex: <BR />
       * >> SetAlarmLEDFlag(0, OVERLOAD_ERROR_FLAG | RANGE_ERROR_FLAG | OVERHEATING_ERROR_FLAG);<BR />
       * >> // �ߕ��ׁA���x�͈͊O�Ɛݒ�l�͈͊O�̏ꍇ�Ɏ����I��LED�_���B
       *
       * @param id ���[�^��ID�ԍ�
       * @param flag �G���[�t���O�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @endif
       *
       * @see INSTRUCTION_ERROR_FLAG
       * @see OVERLOAD_ERROR_FLAG
       * @see CHECKSUM_ERROR_FLAG
       * @see RANGE_ERROR_FLAG
       * @see OVERHEATING_ERROR_FLAG
       * @see ANGLE_LIMIT_ERROR_FLAG
       * @see INPUT_VOLTAGE_ERROR_FLAG
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetAlarmLEDFlag(uint8_t id, uint8_t flag, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief �A���[�����������ꍇ�̎����g���N�I�t�ݒ���擾
       *
       * �Ή�����t���O��ON�ɂȂ��Ă���ƁA�G���[�����������ꍇ�Ƀg���N�I�t�ɂȂ�B
       * �f�t�H���g��0x24 ( Overload, Range Error )
       *
       * <BR />
       * ex: <BR />
       * >> uint8_t buf = GetAlarmShutdownFlag(0);<BR />
       * >> if (buf & OVERLOAD_ERROR_FLAG) { <BR />
       * >> // �ߕ��ׁA���x�͈͊O�Ɛݒ�l�͈͊O�̏ꍇ�Ɏ����I�Ƀg���N�I�t�Ȃ��
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return �G���[�t���O�B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see INSTRUCTION_ERROR_FLAG
       * @see OVERLOAD_ERROR_FLAG
       * @see CHECKSUM_ERROR_FLAG
       * @see RANGE_ERROR_FLAG
       * @see OVERHEATING_ERROR_FLAG
       * @see ANGLE_LIMIT_ERROR_FLAG
       * @see INPUT_VOLTAGE_ERROR_FLAG
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint8_t GetAlarmShutdownFlag(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

      /** 
       * @if jp
       * @brief �A���[�����������ꍇ�̎���LED�_���ݒ���擾
       *
       * �Ή�����t���O��ON�ɂȂ��Ă���ƁA�G���[�����������ꍇ��LED�_���ɂȂ�B
       * �f�t�H���g��0x24 ( Overload, Range Error )
       *
       * <BR />
       * ex: <BR />
       * >> uint8_t buf = GetAlarmShutdownFlag(0);<BR />
       * >> if (buf & OVERLOAD_ERROR_FLAG) { <BR />
       * >> // �ߕ��ׁA���x�͈͊O�Ɛݒ�l�͈͊O�̏ꍇ�Ɏ����I��LED�_���Ȃ��
       *
       * @param id ���[�^��ID�ԍ�
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @return �G���[�t���O�B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @see INSTRUCTION_ERROR_FLAG
       * @see OVERLOAD_ERROR_FLAG
       * @see CHECKSUM_ERROR_FLAG
       * @see RANGE_ERROR_FLAG
       * @see OVERHEATING_ERROR_FLAG
       * @see ANGLE_LIMIT_ERROR_FLAG
       * @see INPUT_VOLTAGE_ERROR_FLAG
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      uint8_t  GetAlarmLEDFlag(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);



      /** 
       * @if jp
       * @brief �R���v���C�A���X�̌X����ݒ肷��
       *
       * @param id ���[�^��ID�ԍ�
       * @param slope �X���[�v
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetComplianceSlope(uint8_t id, uint8_t slope,  int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);



      /** 
       * @if jp
       * @brief �R���v���C�A���X�̕��i�s���сj��ݒ肷��
       *
       * @param id ���[�^��ID�ԍ�
       * @param margin ���B�f�t�H���g��1�B
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetComplianceMargin(uint8_t id, uint8_t margin, int32_t mask=0x7F,  int32_t timeout=DEFAULT_RESPONSE_TIME);



      /** 
       * @if jp
       * @brief ���[�^�ɗ����ŏ��̓d��
       *
       * @param id ���[�^��ID�ԍ�
       * @param punch ���[�^�ɗ����d���B[0, 1024]
       * @param mask �X���[������O�̃}�X�N�B��O�t���O�̑Ή��r�b�g��1�Ȃ�Η�O���X���[�����B0�Ȃ��TimeOut�ȊO�̗�O�̓X���[����Ȃ��B
       * @param timeout �^�C���A�E�g���ԁB�P��ms�B����ȏ�̎��Ԃ�҂��Ă��p�P�b�g���߂�Ȃ��ꍇ��CTimeOutException���X���[�����B
       * @else
       *
       * @brief Set ID Number
       * @param id ID of Motor
       * @return Angle Limit Value
       * @endif
       *
       * @exception ssr::system::CComAccessException
       * @exception ssr::dynamixel::ReceivePacketException
       * @exception ssr::dynamixel::WritePacketException
       * @exception ssr::dynamixel::TimeOutException
       * @exception ssr::dynamixel::AngleLimitException
       * @exception ssr::dynamixel::ChecksumException
       * @exception ssr::dynamixel::InputVoltageException
       * @exception ssr::dynamixel::InstructionException
       * @exception ssr::dynamixel::OverheatingException
       * @exception ssr::dynamixel::OverloadException
       * @exception ssr::dynamixel::RangeException
       */
      void SetPunch(uint8_t id, uint16_t punch,  int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);


      void TorqueEnable(uint8_t id, int32_t mask=0x7F, int32_t timeout=DEFAULT_RESPONSE_TIME);

    };

  }


#define ADDRESS_MODEL_NUMBER      0   //W
#define ADDRESS_VERSION_FW        2   //B
#define ADDRESS_ID                3   //B
#define ADDRESS_BAUDRATE          4   //B
#define ADDRESS_RETURN_DELAY_TIME 5   //B
#define ADDRESS_CW_ANGLE_LIMIT    6   //W
#define ADDRESS_CCW_ANGLE_LIMIT   8   //W
#define ADDRESS_HIGHEST_LIMIT_TEMPERATURE 11 //B
#define ADDRESS_LOWEST_LIMIT_VOLTAGE 12  //B
#define ADDRESS_HIGHEST_LIMIT_VOLTAGE 13 //B
#define ADDRESS_STATUS_RET_LEVEL  16  //B
#define ADDRESS_ALARM_LED	      17
#define ADDRESS_ALARM_SHUTDOWN    18

#define ADDRESS_TORQUE_ENABLE     24  //B
#define ADDRESS_LED               25  //B

#define ADDRESS_CW_COMP_MARGIN    26  //B
#define ADDRESS_CCW_COMP_MARGIN   27  //B
#define ADDRESS_CW_COMP_SLOPE     28  //B
#define ADDRESS_CCW_COMP_SLOPE    29  //B

#define ADDRESS_GOAL_POSITION     30  //W
#define ADDRESS_GOAL_SPEED        32  //W
#define ADDRESS_TORQUE_LIMIT      34  //W
#define ADDRESS_PRESENT_POSITION  36  //W
#define ADDRESS_PRESENT_SPEED     38  //W
#define ADDRESS_PRESENT_LOAD      40  //W
#define ADDRESS_PRESENT_VOLTAGE   42  //B
#define ADDRESS_PRESENT_TEMP      43  //B
#define ADDRESS_MOVING            46  //B
#define ADDRESS_LOCK              47  //B
#define ADDRESS_PUNCH             48  //W

}
