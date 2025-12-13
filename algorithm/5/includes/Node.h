#pragma once

typedef struct __node {
	int data;//ノードの値
	int count;//そのノードが持つ子ノードの数
	struct __node *child; //動的に増減するポインタ配列
} Node;

/*        [10]
         /  |  \
     [5]  [8] [12]

	 //data = 10
	 //count = 3
	 //child[0] = [5],child[1] = [8], child[2] = [12]
*/
        
