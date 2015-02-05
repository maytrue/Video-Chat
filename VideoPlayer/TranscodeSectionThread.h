#pragma once

#include "AVPlaySuite.h"

typedef struct TranscodeSectionParams TranscodeSection;

//ȫ�ֱ�����ʼ���Լ���Ƶ��ʼ��
BOOL ts_Initialize();

//�����߳�
TranscodeSection* ts_CreateTranscodeSection();


//��������Դ������֮ǰ����ɾ���ɵ�����Դ������Դ������֮ǰ�����Ǵ򿪵ġ�
//����ȥ������Դ���ܵ���close
BOOL ts_SetInputSuite(TranscodeSection *p, AVInputSuite *pSuite);
void ts_DeleteInputSuite(TranscodeSection *p);


//������Դ�����֮ǰ���Դ�����Ǵ򿪵ġ�
BOOL ts_AddOutputSuite(TranscodeSection *p, AVOutputSuite *pSuite);
void ts_DeleteAllOutputSuite(TranscodeSection *p);


#ifdef WIN32
//���ò�����Ƶ�Ŀؼ�
BOOL ts_SetWindow(TranscodeSection *p, CWnd *pDlg, UINT nImageCtrlID);
void ts_UnsetWindow(TranscodeSection *p);
#endif


void ts_OpenSound(TranscodeSection *p);
void ts_CloseSound(TranscodeSection *p);
void ts_SetVolumn(TranscodeSection *p, int volumn);


void ts_OpenRecorder(TranscodeSection *p);
void ts_CloseRecorder(TranscodeSection *p);

//�˳��̣߳��˳�ʱ���Զ����ռ�õ��ڴ�
int ts_DestroyTranscodeSection(TranscodeSection **pp);
