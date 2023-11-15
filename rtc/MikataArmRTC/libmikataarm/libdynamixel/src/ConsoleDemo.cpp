/*
 * ConsoleDemo.cpp
 *
 * �R���\�[���v���O�����̗�B
 *
 * author: Hirotaka Hachiya, Yuki Suga (RevatCo., Ltd.)
 *
 * copyright: Revast Co., Ltd. 2010
 * 
 */


#include <signal.h>
#include <string>
#include <iostream>
#include <sstream>

#ifdef WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif


#include <math.h>
#include "Tsurugi.h"

using namespace std;
using namespace revast;
using namespace revast::arm;



/*
 * CConsoleDemo�N���X�B
 *
 * �R���\�[���f���p�N���X�B�R���X�g���N�^�ɂقƂ�ǂ̏������L�q���Ă���B
 *
 * author: Hirotaka Hachiya, Yuki Suga (Revast Co., Ltd.)
 */
class CConsoleDemo {
public:

	/*
	 * Tsurugi�N���X�̃C���X�^���X�B
	 */
	CTsurugi myArm;

	/*
	 * �e�֐߂̊p�x�w�߂��s���ꍇ�́A����X�e�b�v�B�����l5.0�B
	 */
	double step;


	/*
	 * �֐߂̐�
	 */
	static const int NUM_JOINT = 6;


	/*
	 * �e�B�[�`���O�ŋL���\�ȃo�b�t�@�̐��B
	 */
	static const int NUM_BUFFER = 1024;

	/*
	 * �e�B�[�`���O�Ŋ֐ߊp�x��ۑ����邽�߂̃o�b�t�@�B
	 */
	double PositionBuffer[NUM_JOINT][NUM_BUFFER];

	/*
	 * �e�B�[�`���O�ŕۑ������|�W�V�����̐��B
	 */
	int CurrentBufferPosition;
public:
	
	/*
	 * �R���X�g���N�^
	 *
	 * ���C���֐��̂قƂ�ǂ̏����͂����ɋL�q���Ă���B
	 *  argc main�֐��̈���1�D�R�}���h���C�������̐��{�P
	 *  argv main�֐��̈���2�D�R�}���h���C������������킷������B0�Ԗڂ̓R�}���h���̂��̂��́B
	 */
	CConsoleDemo(int argc, char* argv[]): CurrentBufferPosition(0), step(5.0) {

		string comportName; // �ʐM�|�[�g�̃t�@�C����
		ostringstream oss;  // �t�@�C�������쐬���邽�߂̃X�g���[���B 


		cout << "Input COM Port Name.... >> ";
		std::string lineBuffer, dummy;
		std::getline(std::cin, lineBuffer);
		//oss << "Port = " << lineBuffer;
		comportName = lineBuffer;
		
		// �ʐM�|�[�g���J��
		cout << "COM PORT OPEN [" << comportName << "]" << endl;
		try {
			myArm.Connect(comportName.c_str(), 57600);
			Initialize(); // �������B
		} catch (CException &e) {
			cout << "Exception occurred." << endl;
			cout << ">> " << e.what() << endl;
			cout << "Aborted." << endl;
			exit(-1);
		}

		cout << "Input Command ( 'h'=help ) >> " << ends;
		int endflag = FALSE; // �I���t���O�BTRUE��While�𔲂���B
		char ch;
		while(!endflag) {

			try {
				  std::cout << "Input Command and Enter." << std::endl;
				  std::getline(std::cin, lineBuffer);
				  ch = lineBuffer[0];
					switch(ch){
						case 'h': // �w���v�\��
							Help();
							break;
						case 0x1B: // "ESC"�͏I��
							endflag = TRUE;
							break;
						case 'p': // ���݈ʒu�\��
							ShowCurrentPosition();
							break;
						case 'v': // ���ݑ��x�\��
							ShowCurrentVelocity();
							break;
						case 'V': // �ڕW���x�ύX
							ChangeTargetVelocity();
							break;
						case 'F': // �g���N���~�b�g�ύX
							ChangeLimitTorque();
							break;
						case '1': //1: increase motor 1 position
							MoveRelatively(0, step);
							break;
						case '!': //Shift+1: decrese motor 1 position
							MoveRelatively(0, -step);
							break;
						case '2': //2: increase motor 2 position
							MoveRelatively(1, step);
							break;
						case '"': //Shift+2: decrese motor 2 position
							MoveRelatively(1, -step);
							break;
						case '3': //3: increase motor 1 position
							MoveRelatively(2, step);
							break;
						case '#': //Shift+3: decrese motor 1 position
							MoveRelatively(2, -step);
							break;
						case '4': //4: increase motor 1 position
							MoveRelatively(3, step);
							break;
						case '$': //Shift+4: decrese motor 1 position
							MoveRelatively(3, -step);
							break;
						case '5': //5: increase motor 1 position
							MoveRelatively(4, step);
							break;
						case '%': //Shift+5: decrese motor 1 position
							MoveRelatively(4, -step);
							break;
						case '6': //6: increase motor 1 position
							MoveRelatively(5, step);
							break;
						case '&': //Shift+6: decrese motor 1 position
							MoveRelatively(5, -step);
							break;
						case '7': // Close Hand;
							myArm.Hand->Close();
							break;
						case '8': // Open Hand;
							myArm.Hand->Open();
							break;
						case 's': // ���Z�I�ȓ���̃X�e�b�v���ύX
							ChangeStep();
							break;
						case 't':  //Motor torque on
							cout << "Motor torque ON" << endl;
							myArm.ServoOn();
							break;
						case 'T': // Motor torque off
							cout << "Motor torque OFF" << endl;
							myArm.ServoOff();
							break;
						case 'a': // add current position
							ShowCurrentPosition();
							RecordCurrentPosition();
							break;
						case 'c': // clear position buffer;
							ClearPositionBuffer();
							break;
						case 'r': // �ۑ����ꂽ�ʒu���\���B
							ShowRecordedPosition();
							break;
						case 'g': // �v���C�o�b�N����B
							PlayRecordedPosition();
							break;
						case 'o': // �����ʒu�ֈړ�
							myArm.Joint[0]->MoveImmediately(0);
							myArm.Joint[1]->MoveImmediately(0);
							myArm.Joint[2]->MoveImmediately(0);
							myArm.Joint[3]->MoveImmediately(0);
							myArm.Joint[4]->MoveImmediately(0);
							myArm.Joint[5]->MoveImmediately(0);
							break;
						default:
							cout << "Unknown Command." << endl;
							Help();
							break;
					} // switch
					cout << "Input Command ( 'h'=help ) >> " << ends;

			} catch (CException &e) {
				cout << "Exception occurred." << endl;
				cout << ">> " << e.what() << endl;
			}
		} // while
	}
		

	/*
	 * �f�X�g���N�^
	 */
	virtual ~CConsoleDemo() {}


public:

	/*
	 * ����������
	 *
	 * myArm�̃g���N���I���ɂ���B
	 */
	void Initialize() {
		myArm.ServoOn();
	}

	/*
	 * �v���C�o�b�N����B
	 *
	 * �L�^�����|�W�V�����̍ŏ�����Ō�܂ŃA�[���𓮂����B
	 * �e�֐߂�5�x�ȓ��̌덷�ɓ���܂œ���𑱂���̂ŁA���׏󋵂ɂ���Ă͏I�����Ȃ��\��������B
	 */
	void PlayRecordedPosition() {
		cout << "Are you ready for replaying? (Yes: y or No:n) [n]";

		std::string lineBuffer;
		std::getline(std::cin, lineBuffer);
		char c = lineBuffer.c_str()[0];
		if(c == 'y'){
			for(int i = 0;i < CurrentBufferPosition;i++) {
				for(int j = 0;j < myArm.GetNumJoint();j++) {
					myArm.Joint[j]->MoveImmediately(PositionBuffer[j][i]);
				}

				for(int j = 0;j < myArm.GetNumJoint();j++) {
					while(1) {
#ifdef WIN32
						Sleep(10); // Wait 10 [ms]
#else
						usleep(10*1000);
#endif
						double delta = fabs(myArm.Joint[j]->GetCurrentPosition() - PositionBuffer[j][i]);
						if(delta < 5) {
							break;
						}
					}
				}
			}
		}
		cout <<("Done.\n");
	}

	/*
	 * �ۑ������|�W�V�����f�[�^�̕\��
	 */
	void ShowRecordedPosition() {
		if(CurrentBufferPosition > 0){
			for(int i = 0;i < CurrentBufferPosition;i++) {
				cout << "Position[" << i << "]:";
				for(int j = 0;j < myArm.GetNumJoint();j++) {
					cout << PositionBuffer[j][i];
					if(j != myArm.GetNumJoint()-1) {
						cout << ", ";
					} else {
						cout << endl;
					}
				}
			}
		}else{
			cout << "No Record." << endl;
		}
	}

	/*
	 * ���݈ʒu���|�W�V�����o�b�t�@�ɕۑ�����B
	 */
	void RecordCurrentPosition() {
		for(int i = 0;i < myArm.GetNumJoint();i++) {
			PositionBuffer[i][CurrentBufferPosition] = myArm.Joint[i]->GetCurrentPosition();
		}
		cout << "Recorded." << endl;
		CurrentBufferPosition++;
	}

	/*
	 * �|�W�V�����o�b�t�@���N���A
	 */
	void ClearPositionBuffer() {
		cout << "Do you really want to clear registered positions? (Yes: y or No:n) [n] >> ";

		std::string lineBuffer;
		std::getline(std::cin, lineBuffer);
		char c = lineBuffer.c_str()[0];
		if(c == 'y'){
			CurrentBufferPosition = 0;
			cout << "Positions are cleared." << endl;
		}
   	}


	/*
	 * ���݈ʒu����step�����֐߂𓮂���
	 *  joint �֐ߔԍ��B0�`5
	 *  step ����p�x
	 */
	void MoveRelatively(int joint, double step) {
		myArm.Joint[joint]->MoveImmediately(myArm.Joint[joint]->GetCurrentPosition() + step);
	}

	/*
	 * step�̒l��ύX����B
	 *
	 */
	void ChangeStep() {
		cout << "Incremental/decremental step: " << step << endl;
		cout <<"Do you want to change? (Yes: y or No:n) [n]";

		std::string lineBuffer;
		std::getline(std::cin, lineBuffer);
		char c = lineBuffer.c_str()[0];
		if(c == 'y'){
			cout <<"Incremental/decremental step (0, 10]>>";
			std::getline(std::cin, lineBuffer);
			double buf = atof(lineBuffer.c_str());
			if(buf > 0, buf <= 10) {
				step = buf;
			} else {
				cout << "Wrong Value." << endl;
			}
		}
	}

	/*
	 * �g���N�����l�̕ύX
	 */
	void ChangeLimitTorque() {
		ShowLimitTorque();

		cout << "Do you want to change? (Yes: y or No:n) [n]";

		std::string lineBuffer;
		std::getline(std::cin, lineBuffer);
		char c = lineBuffer.c_str()[0];
		if(c == 'y'){
			cout << "Limit Torque [0, 100] [unit: %] : >> ";
			std::getline(std::cin, lineBuffer);
			double limit = atof(lineBuffer.c_str());
			if(limit >= 0 && limit <= 100) {
				for(int i = 0;i < myArm.GetNumJoint();i++) {
					myArm.Joint[i]->SetTorqueLimit(limit);
				}
			} else {
				cout << "Wrong Limit Value." << endl;
			}
		}
	}

	/*
	 * ���x�����l�̕ύX
	 */
	void ChangeTargetVelocity() {
		ShowTargetVelocity();

		cout << "Do you want to change? (Yes: y or No:n) [n]";

		std::string lineBuffer;
		std::getline(std::cin, lineBuffer);
		char c = lineBuffer.c_str()[0];
		if(c == 'y'){
			cout << "Target speed (0, 30) [unit: rpm]: >> ";
			std::getline(std::cin, lineBuffer);
			double vel = atof(lineBuffer.c_str());
			if(vel > 0 && vel < 30) {
				for(int i = 0;i < myArm.GetNumJoint();i++) {
					myArm.Joint[i]->SetTargetVelocity(vel);
				}
			} else {
				cout << "Wrong Speed." << endl;
			}
		}
	}

	/*
	 * �g���N�����l��\���B�P�ʂ͍ő�̃��[�^�o�͂ɑ΂��銄��[��]�B
	 */
	void ShowLimitTorque() {
		cout << "Limit Torque: ";
		for(int i = 0;i < myArm.GetNumJoint();i++){
			cout << myArm.Joint[i]->GetCurrentPosition();
			if(i != myArm.GetNumJoint()-1) {
				cout << ", ";
			} else {
				cout << endl;
			}
		}
	}

	/*
	 * ���݂̃��[�^�̈ʒu�\��
	 */
	void ShowCurrentPosition() {
		cout << "Current Position: ";
		for(int i = 0;i < myArm.GetNumJoint();i++){
			cout << myArm.Joint[i]->GetCurrentPosition();
			if(i != myArm.GetNumJoint()-1) {
				cout << ", ";
			} else {
				cout << endl;
			}
		}
	}

	/*
	 * ���݂̃��[�^�̑��x�\��
	 */
	void ShowCurrentVelocity() {
		cout << "Current Velocity: ";
		for(int i = 0;i < myArm.GetNumJoint();i++){
			cout << myArm.Joint[i]->GetCurrentVelocity();
			if(i != myArm.GetNumJoint()-1) {
				cout << ", ";
			} else {
				cout << endl;
			}
		}
	}

	/*
	 * ���݂̃��[�^�̖ڕW���x�\��
	 */
	void ShowTargetVelocity() {
		cout << "Target Velocity: ";
		for(int i = 0;i < myArm.GetNumJoint();i++){
			cout << myArm.Joint[i]->GetTargetVelocity();
			if(i != myArm.GetNumJoint()-1) {
				cout << ", ";
			} else {
				cout << endl;
			}
		}
	}



	/*
	 * �v���O�������̃L�[�{�[�h�R�}���h�̕\���i�w���v�j
	 */
	void Help() {
        cout << endl << "-----------------------------------------------" << endl;
        cout << "* Show this menu (h)" << endl;            
        cout << "* Read current positions of motors (p)" << endl;
        cout << "* Read current speed of motors (v)" << endl;
        cout << "* Change speed of motors (V)" << endl;
        cout << "* Change torque-limit of motors (F)" << endl;        
        cout << "* Open gripper (o)" << endl;
        cout << "* Close gripper (c)" << endl;        
        cout << "* Finish this demo program (Esc)" << endl;        
        cout << endl;        
        cout << "* Motor position control" << endl;
        cout << " -Increase motor 1 (1)" << endl;
        cout << " -Decrease motor 1 (Shift+1)" << endl;
        cout << " -Increase motor 2 (2)" << endl;
        cout << " -Decrease motor 2 (Shift+2)" << endl;
        cout << " -Increase motor 3 (3)" << endl;
        cout << " -Decrease motor 3 (Shift+3)" << endl;
        cout << " -Increase motor 4 (4)" << endl;
        cout << " -Decrease motor 4 (Shift+4)" << endl;
        cout << " -Increase motor 5 (5)" << endl;
        cout << " -Decrease motor 5 (Shift+5)" << endl;
        cout << " -Increase motor 6 (6)" << endl;
        cout << " -Decrease motor 6 (Shift+6)" << endl;
        cout << " -Hand Close (7)" << endl;
        cout << " -Hand Open  (8)" << endl;        
        cout << " -Read and change step size (s)" << endl;
        cout << endl;
        cout << "* Teaching and replay" << endl;
        cout << " -Motor torque on (t)" << endl;
        cout << " -Motor torque off (T)" << endl;
        cout << " -Add current position (a)" << endl;
        cout << " -Clear registerd positions (c)" << endl;
        cout << " -Show registered positions (r)" << endl;
        cout << " -Replay registered positions (g)" << endl;
		cout << " -Move to initial position (o)" << endl;
        cout << "-----------------------------------------------" << endl;
	}

};




/*
 * main�֐�
 *
 * CConsoleDemo�N���X�̃C���X�^���X���쐬����̂݁B
 * ��ȏ����͂��ׂ�CConsoleDemo�N���X�̃R���X�g���N�^�ɋL�q���Ă���B
 *
 * @see CConsoleDemo
 */
int main(int argc, char* argv[])
{
	CConsoleDemo(argc, argv);
	return 0;
}
