#ifndef GLOBAL_H
#define GLOBAL_H
typedef struct tagVertex
{
	int row;   //�к�
	int col;   //�к�
	int info;
}Vertex;
//��ʾΪ��
#define BLANK           -1   //ͼƬ�������ı�־
#define MAX_ROW         10   //��Ϸ��ͼ������
#define MAX_COL         16   //��Ϸ��ͼ������
#define MAX_VERTEX_NUM 160   //������
#define MAX_PICNUM      16   //ͼƬ��ɫ
#define REPEAT_NUM      10   //ÿ�ֻ�ɫͼƬ����
#define MAP_TOP         50   //��Ϸ��ͼ���Ͻ�������
#define MAP_LEFT        20   //��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH       40   //��ϷͼƬ���
#define PIC_HEIGHT      40   //��ϷͼƬ�߶�
#define PLAY_TIMER_ID   1    //��ʱ������ʱ��1s
#define GAME_LOSE       -1   //ʧ��
#define GAME_SUCCESS    0    //��ʤ
#define GAME_PLAY       1    //��Ϸ���ڽ���
#endif
