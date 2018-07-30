#ifndef GLOBAL_H
#define GLOBAL_H
typedef struct tagVertex
{
	int row;   //行号
	int col;   //列号
	int info;
}Vertex;
//表示为空
#define BLANK           -1   //图片被消除的标志
#define MAX_ROW         10   //游戏地图的行数
#define MAX_COL         16   //游戏地图的列数
#define MAX_VERTEX_NUM 160   //顶点数
#define MAX_PICNUM      16   //图片花色
#define REPEAT_NUM      10   //每种花色图片个数
#define MAP_TOP         50   //游戏地图左上角纵坐标
#define MAP_LEFT        20   //游戏地图左上角横坐标
#define PIC_WIDTH       40   //游戏图片宽度
#define PIC_HEIGHT      40   //游戏图片高度
#define PLAY_TIMER_ID   1    //计时器触发时间1s
#define GAME_LOSE       -1   //失败
#define GAME_SUCCESS    0    //获胜
#define GAME_PLAY       1    //游戏正在进行
#endif
