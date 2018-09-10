#include "OGSystem\OGsystem.h"
/**
*@brief	:�Q�[���i�s�Ǘ�class
*/
class GameManager : public TaskObject
{
	//!	�o�ߕb�^�C��
	unsigned int Seconds;
	//!	�o�ߕ��^�C��
	unsigned int Minute;
	//!	�o�߃J�E���g
	unsigned int timeCnt;
	//!	�Q�[���N���A��Q�[���I������܂ł̎���
	unsigned int time;
	//! �N���A���
	bool isclear;
	//!	�~�b�V�����N���A���
	bool M_flag[3];	
	//!	�X�}�[�g�|�C���^
	typedef std::shared_ptr<GameManager> SP;
	/**
	*@brief	:�^�C�}�[�̏���m�F
	*@return:bool �^�C�}�[����ɒB���Ă����ꍇtrue
	*/
	bool isMaxTime();
	/**
	*@brief	:���̋L�^��ۑ�����
	*@return:bool �ۑ��ɐ��������true
	*/
	bool OutData();
	/**
	*@brief	:�O�܂ł̍ō��L�^�Ɣ�r���悢����ۑ�����
	*@return:bool �ő�L�^�̕ۑ��ɐ��������true
	*/
	bool ComparisonData();
	/**
	*@brief	:���݂̃f�[�^�����̂܂ܕۑ�����
	*/
	void OutFileData();
	/**
	*@brief	:constructor	�e�l�̏�����
	*/
	explicit GameManager();
	/**
	*@brief	:�X�V����
	*/
	void UpDate() override;
public:
	/**
	*@brief	:�N���A�󋵂�Ԃ�
	*@return:bool �Q�[���N���A���Ă����true
	*/
	bool isClear();
	/**
	*@brief	:���݂̕b�^�C����Ԃ�
	*@return:unsigned int �b�^�C��
	*/
	unsigned int SecondsTime() const;
	/**
	*@brief	:���݂̕��^�C����Ԃ�
	*@return:unsigned int ���^�C��
	*/
	unsigned int MinuteTime() const;
	/**
	*@brief	:�Z�[�u�f�[�^�̏�����
	*/
	static void ResetData();
	/**
	*@brief	:�S�f�[�^�̈Í���
	*/
	static void DataEncryption();
	/**
	*@brief	:destructor	�������^�X�N���w�肷��
	*/
	virtual ~GameManager();
	/**
	*@brief	:�^�X�N����
	*@reutrn:GameManager	�����Ɏ��s�����ꍇ��nullptr
	*/
	static SP Create();
};