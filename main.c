#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define row 25

/*----------------------------------------------------------*/
/*                                                          */
/*  TODO:                                                   */
/*                                                          */
/*      add hold                                            */
/*                                                          */
/*      preview                                             */
/*                                                          */
/*      animation game start                                */
/*                                                          */
/*                                                          */
/*----------------------------------------------------------*/


/*----------------------------------------------------------*/
/*                                                          */
/*     bricks                                               */
/*                                                          */
/*    1. square        2. L shape 1        3. L shape 2     */
/*                                                          */
/*    ########          ##########          ##########      */
/*    ##    ##          ##      ##          ##      ##      */
/*    ##    ##          ######  ##          ##  ######      */
/*    ########          ##########          ##########      */
/*                                                          */
/*                                                          */
/*  4. S shape 1       5. S shape 2         6. T shape      */
/*                                                          */
/*   ##########         ##########          ##########      */
/*   ####    ##         ##    ####          ##      ##      */
/*   ##    ####         ####    ##          ####  ####      */
/*   ##########         ##########          ##########      */
/*                                                          */
/*                      7. I shape                          */
/*                                                          */
/*                     ############                         */
/*                     ##        ##                         */
/*                     ############                         */
/*                                                          */
/*----------------------------------------------------------*/

int BRICK_START_POINT[7][2] = {5, 0, 
                               5, 0, 
                               5, 0, 
                               5, 0, 
                               5, 0, 
                               5, 0, 
                               5, 0,};

int BRICKS_AND_ROTATIONS_AND_BLOCK_POSITIONS[7][4][8] = \
   {0, 0, 1, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 1, 1, 1,  0, 0, 1, 0, 0, 1, 1, 1,
    0, 1, 1, 1, 2, 1, 2, 2,  1, 0, 1, 1, 0, 2, 1, 2,  0, 0, 0, 1, 1, 1, 2, 1,  1, 0, 2, 0, 1, 1, 1, 2,
    0, 1, 1, 1, 2, 1, 0, 2,  0, 0, 1, 0, 1, 1, 1, 2,  2, 0, 0, 1, 1, 1, 2, 1,  1, 0, 1, 1, 1, 2, 2, 2,
    1, 1, 2, 1, 0, 2, 1, 2,  0, 0, 0, 1, 1, 1, 1, 2,  1, 1, 2, 1, 0, 2, 1, 2,  0, 0, 0, 1, 1, 1, 1, 2,
    0, 1, 1, 1, 1, 2, 2, 2,  1, 0, 0, 1, 1, 1, 0, 2,  0, 1, 1, 1, 1, 2, 2, 2,  1, 0, 0, 1, 1, 1, 0, 2,
    0, 1, 1, 1, 2, 1, 1, 2,  1, 0, 0, 1, 1, 1, 1, 2,  1, 0, 0, 1, 1, 1, 2, 1,  1, 0, 1, 1, 2, 1, 1, 2,
    0, 2, 1, 2, 2, 2, 3, 2,  1, 0, 1, 1, 1, 2, 1, 3,  0, 2, 1, 2, 2, 2, 3, 2,  1, 0, 1, 1, 1, 2, 1, 3};

struct BRICK_INFO {
    int position[2];
    int brick_type;
    int cordinates[8];
    int rotation;
} falling_brick;





long score = 0;
long lines = 0;

int fixed_blocks[row][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int main_grid[row][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int upcoming_bricks[5];

long game_time;
long cpu_time;
long last_cpu_time;

int state = 0;

int time_from_last_brick_fall = 0;
int brick_fall_interval;




void print_array(int *array, int size)
{
    printf("[");
    for (int i=0; i<size; i++)
        printf("%d, ", array[i]);
    printf("\033[2D]");
}

int areSameArray(int *arr_1, int *arr_2, int arr_size)
{
    for (int i=0; i<arr_size; i++)
    {
        if (arr_1[i] != arr_2[i])
            return 0;
    }
    return 1;
}


/*---------------------------------------------------------------------*/
/*                                                                     */
/*          This is a brick                 These are the blocks       */
/*                                                                     */
/*            ##########                    ####################       */
/*            ##    ####                    ######  ########  ##       */
/*            ####    ##                    ######  ########  ##       */
/*            ##########                    ####      ######  ##       */
/*                                          ####        ##    ##       */
/*                                          ####        ####  ##       */
/*                                          ####        ####  ##       */
/*                                          ##          ##    ##       */
/*                                          ####################       */
/*                                                                     */
/*---------------------------------------------------------------------*/



/*-------------------------------------------------------*
 *              brick controlling functions              *
 *-------------------------------------------------------*/


/*--------brick movement functions--------*/
int moveFallingBrickOnestep(int, int);

int moveBrickOnestep(int, int, struct BRICK_INFO*);
/* direction value*/
/* vertical movement ; 1  */
/* horizonal movement ; 0 */

/* movement should be 1 or -1. */

int rotateBrickRight(void);

int rotateBrickLeft(void);

/*return value of these functons are explaining is it moved successfuly(1) or not(0).*/

void hardDrop(void);

/*----------------------------------------*/


struct BRICK_INFO reCalculateBrickCordinate(struct BRICK_INFO);

int newBrick(void);

int isBrickMovableTo(int *);
/*argument should be 2x4 array expressed as array length of 8.*/

void fixFallingBrick(void);

int detectAndDeleteFullRow(void);


/*--------------------------------------------------------*/
/*                                                        */
/*--------------------------------------------------------*/



/*-------------------------------------------------------*
 *                   Graphics functions                  *
 *-------------------------------------------------------*/

void drawFixedBlocks(void);

void drawBrick(struct BRICK_INFO);

int gameoverAndAskContinue(void);

int pauseMenu(void);

/*--------------------------------------------------------*/
/*                                                        */
/*--------------------------------------------------------*/




/*-------------------------------------------------------*
 *                    Console functions                  *
 *-------------------------------------------------------*/

void hideConsoleCursor(void);

void showConsoleCursor(void);

void moveCursor(int, int);

void printColoredBlock(int);

void printSingleBrick(int *, int);

void initRenderGame(void);

void renderLeftSide(int y);

void renderRightSide(int y);

void renderGame(void);


/*--------------------------------------------------------*/
/*                                                        */
/*--------------------------------------------------------*/





/*==========================================================================* 
 **************************************************************************** 
 *                                                                          * 
 *                    just emphasising the main function                    * 
 *                                                                          * 
 **************************************************************************** 
 *==========================================================================*/

int main()
{
    int keyboard_input;
    int arrow_code;

    hideConsoleCursor();

    printf("\n\n\n");
    printf("                    block stacker\n");

    GAME_START:

    state = 0;
    score = 0;
    lines = 0;

    time_from_last_brick_fall = 0;
    for (int i=0; i<row; i++)
    {
        for (int j=0; j<10; j++)
        {
            fixed_blocks[i][j] = 0;
        }
    }

    srand((unsigned int)time(NULL));

    brick_fall_interval = 500;

    for (int i=0; i<5; i++)
        upcoming_bricks[i] = rand()%7+1;
    newBrick();

    initRenderGame();

    game_time = 0;
    cpu_time = clock();
    last_cpu_time = cpu_time;

    while (state == 0)
    {
        cpu_time = clock();
        time_from_last_brick_fall += cpu_time - last_cpu_time;
        game_time += cpu_time - last_cpu_time;

        for (int i=0;i<10;i++)
        {
            if (kbhit())
            {
                keyboard_input = getch();
                switch (keyboard_input) 
                {
                    case 0x1b:
                        state = pauseMenu();
                        time_from_last_brick_fall = 0;
                        cpu_time = clock();
                        break;
                    case 0xe0:
                        arrow_code = getch();
                        switch (arrow_code)
                        {
                            case 0x4b:
                                moveFallingBrickOnestep(0, -1);
                                break;
                            case 0x4d:
                                moveFallingBrickOnestep(0, 1);
                                break;
                            case 0x50:
                                moveFallingBrickOnestep(1, 1);
                                break;
                            case 0x48:
                                hardDrop();
                                time_from_last_brick_fall = brick_fall_interval;
                                break;
                        }
                        break;
                    case 0x7a:
                        rotateBrickLeft();
                        break;
                    case 0x63:
                        rotateBrickRight();
                        break;
                }
            }
        }

        if (time_from_last_brick_fall >= brick_fall_interval)
        {
            for (int i=0; i<time_from_last_brick_fall/brick_fall_interval; i++)
            {
                if(!moveFallingBrickOnestep(1, 1))
                {
                    fixFallingBrick();
                    if (!newBrick())
                    {
                        state = 2;
                        break;
                    }
                    time_from_last_brick_fall = 0;
                }
            }
            time_from_last_brick_fall %= brick_fall_interval;
        }

        if (detectAndDeleteFullRow())
            time_from_last_brick_fall = 0;

        drawFixedBlocks();
        drawBrick(falling_brick);

        renderGame();
        last_cpu_time = cpu_time;
    }

    switch (state)
    {
        case 2:
            if (gameoverAndAskContinue())
                goto GAME_START;
        default:
            printf("\033[10C\033[25B\n\n\n\n");
            showConsoleCursor();
            return 0;

    }
}


/*==========================================================================*/




int moveFallingBrickOnestep(int direction, int movement)
{
    return moveBrickOnestep(direction, movement, &falling_brick);
}

int moveBrickOnestep(int direction, int movement, struct BRICK_INFO *move_brick)
{
    int move_distance = movement / abs(movement);
    int will_move_to[8];

    for (int i=0; i<8; i++)
    {
        if (i%2==direction)
            will_move_to[i] = move_brick->cordinates[i] + move_distance;
        else
            will_move_to[i] = move_brick->cordinates[i];
    }

    if (isBrickMovableTo(will_move_to))
    {
        memcpy(move_brick->cordinates, will_move_to, sizeof(will_move_to));
        move_brick->position[direction] += move_distance;
        return 1;
    }
    else
        return 0;
}

int rotateBrickLeft(void)
{
    struct BRICK_INFO move_to;
    move_to = falling_brick;

    move_to.rotation = (move_to.rotation + 1) % 4;
    move_to = reCalculateBrickCordinate(move_to);

    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] += 1;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] -= 2;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] += 3;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] -= 4;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }
    else
        return 0;
}

int rotateBrickRight(void)
{
    struct BRICK_INFO move_to;
    move_to = falling_brick;

    move_to.rotation = (move_to.rotation + 3) % 4;
    move_to = reCalculateBrickCordinate(move_to);

    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] += 1;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] -= 2;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] += 3;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }

    move_to.position[0] -= 4;
    move_to = reCalculateBrickCordinate(move_to);
    if (isBrickMovableTo(move_to.cordinates))
    {
        falling_brick = move_to;
        return 1;
    }
    else
        return 0;
}

int isBrickMovableTo(int *move_to)
{
    for (int i=0; i<4; i++)
    {
        if (fixed_blocks[move_to[i*2+1]][move_to[i*2]] != 0 ||
            move_to[i*2+1] >= row ||
            move_to[i*2] >= 10 ||
            move_to[i*2] < 0)
        {
            return 0;
        }
    }
    return 1;
}

void hardDrop(void)
{
    int result;
    do
    {
        result = moveFallingBrickOnestep(1, 1);
        score += 1;
    }
    while (result);
}

void fixFallingBrick(void)
{
    for (int i=0; i<4; i++)
        fixed_blocks[falling_brick.cordinates[i*2+1]][falling_brick.cordinates[i*2]] = falling_brick.brick_type;
}

int newBrick(void)
{
    falling_brick.brick_type = upcoming_bricks[0];
    falling_brick.rotation = 0;
    falling_brick.position[0] = BRICK_START_POINT[falling_brick.brick_type-1][0];
    falling_brick.position[1] = BRICK_START_POINT[falling_brick.brick_type-1][1];
    falling_brick = reCalculateBrickCordinate(falling_brick);
    if (!isBrickMovableTo(falling_brick.cordinates))
        return 0;

    int len_upcoming = sizeof(upcoming_bricks) / sizeof(int);
    for (int i=0; i<len_upcoming; i++)
    {
        if (i >= 1)
            upcoming_bricks[i-1] = upcoming_bricks[i];
    }
    int new_upcoming = rand()%7+1;
    upcoming_bricks[len_upcoming - 1] = new_upcoming;
    return 1;
}

struct BRICK_INFO reCalculateBrickCordinate(struct BRICK_INFO brick_info)
{
    for (int i=0; i<8; i++)
        brick_info.cordinates[i] = BRICKS_AND_ROTATIONS_AND_BLOCK_POSITIONS[brick_info.brick_type-1][brick_info.rotation][i];
    for (int i=0; i<8; i++)
        brick_info.cordinates[i] += brick_info.position[i%2];
    return brick_info;
}

int detectAndDeleteFullRow(void)
{
    int is_row_full[row] = {1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1, 
                            1};

    for (int row_index = 0; row_index<row; row_index++)
    {
        for (int i=0; i<10; i++)
            is_row_full[row_index] *= fixed_blocks[row_index][i];
        if (is_row_full[row_index] > 0)
            is_row_full[row_index] = 1;
    }

    int full_row_exists = 0;

    for (int i=0; i<row; i++)
    {
        if (is_row_full[i] != 0)
        {
            full_row_exists = 1;
            break;
        }
    }

    if (!full_row_exists)
        return 0;

    int fixed_blocks_cpy[row][10];
    int animation_time = 0;
    int last_animation_time = 0;
    long animation_start = clock();

    memcpy(fixed_blocks_cpy, fixed_blocks, sizeof(fixed_blocks));

    int blink_state = 1;
    int time_from_last_blink = 0;
    while (animation_time <= 400)
    {
        animation_time = clock() - animation_start;
        time_from_last_blink += animation_time - last_animation_time;
        for (int i=0; i<row; i++)
        {
            for (int j=0; j<10; j++)
                fixed_blocks_cpy[i][j] = fixed_blocks[i][j] * !(!blink_state&&is_row_full[i]);
        }
        if (time_from_last_blink > 50)
        {
            blink_state = !blink_state;
            time_from_last_blink = 0;
        }
        memcpy(main_grid, fixed_blocks_cpy, sizeof(fixed_blocks_cpy));
        renderGame();
        last_animation_time = animation_time;
    }

    animation_start = clock();
    animation_time = 0;
    last_animation_time = 0;
    int animation_step = 1;
    int j;
    while (animation_time <= 250)
    {
        animation_time = clock() - animation_start;

        animation_step = animation_time / 50 + 1;

        for (int i=0; i<row; i++)
        {
            for (j=0; j<10; j++)
            {
                if (!is_row_full[i])
                    fixed_blocks_cpy[i][j] = fixed_blocks[i][j];
                else if (j < 5)
                    fixed_blocks_cpy[i][j] = ((5-j) <= animation_step)? 0:fixed_blocks[i][j];
                else
                    fixed_blocks_cpy[i][j] = ((j-4) <= animation_step)? 0:fixed_blocks[i][j];
            }
        }
        memcpy(main_grid, fixed_blocks_cpy, sizeof(fixed_blocks_cpy));
        renderGame();
        last_animation_time = animation_time;
    }

    int full_row_amount = 0;
    for (int i=0; i < row; i++)
        full_row_amount += is_row_full[i];

    int full_rows[full_row_amount];
    full_row_amount = 0;
    for (int i=0; i < row; i++)
    {
        if (is_row_full[i])
        {
            full_rows[full_row_amount] = i;
            full_row_amount += 1;
        }
    }

    for (int i=0; i < full_row_amount; i++)
    {
        for (j=row-1; j >= 0; j--)
        {
            if (j<full_rows[i])
                for (int k=0; k < 10; k++)
                    fixed_blocks[j+1][k] = fixed_blocks[j][k];
        }
    }

    
    for (int i=0; i < full_row_amount; i++)
    {
        for (j=0; j < 10; j++)
        {
            fixed_blocks[i][j] = 0;
        }
    }
    

    lines += full_row_amount;
    switch (full_row_amount)
    {
        case 1:
            score += 40;
            break;
        case 2:
            score += 100;
            break;
        case 3:
            score += 300;
            break;
        case 4:
            score += 1200;
            break;
    }

    return 1;
}





void drawFixedBlocks(void)
{
    memcpy(main_grid, fixed_blocks, sizeof(fixed_blocks));
}

void drawBrick(struct BRICK_INFO brick_info)
{
    for (int i=0; i<4; i++)
        main_grid[brick_info.cordinates[i*2+1]][brick_info.cordinates[i*2]] = brick_info.brick_type;
}

int gameoverAndAskContinue(void)
{
    int ANIMATION_STEP_INTERVAL = 20;
    int animation_start = clock();
    int animation_time = clock() - animation_start;
    int animation_step = animation_time / ANIMATION_STEP_INTERVAL;
    int key_input;
    for (int i=0; i<5; i++)
    {
        upcoming_bricks[i] = 10;
    }

    while (animation_step <= row)
    {
        animation_time = clock() - animation_start;
        animation_step = animation_time / ANIMATION_STEP_INTERVAL;

        printf("\n");
        for (int y=0; y<row; y++)
        {
            renderLeftSide(y);
            if (y < animation_step)
            {
                switch (y)
                {
                    case 5:
                        printf("     GAME  OVER     ");
                        break;
                    case 8:
                        printf("  score : %8ld  ", score);
                        break;
                    case 10:
                        printf("  lines : %8ld  ", lines);
                        break;
                    case 13:
                        printf("   press  \033[32m[ENTER]\033[m   ");
                        break;
                    case 14:
                        printf("    to  \033[32mCONTINUE\033[m    ");
                        break;
                    case 17:
                        printf("     press  \033[31mEsc\033[m     ");
                        break;
                    case 18:
                        printf("      to \033[31mEscape\033[m     ");
                        break;
                    default:
                        printf("                    ");
                        break;
                }
            }
            else
            {
            for (int x=0; x<10; x++)
                printColoredBlock(main_grid[y][x]);
            }
            renderRightSide(y);
        }
        printf("######################################################\n");
        printf("\n\n\n");
        printf("\033[10D\033[%dA", row+5);
    }

    while (1)
    {
        if (kbhit())
        {
            key_input = getch();
            switch (key_input)
            {
                case 0x1b:
                    return 0;
                    break;
                case 0x0d:
                    return 1;
                    break;
            }
        }
    }
}

void printPauseMenu(int y)
{
    switch (y)
    {
        case 3:
            printf("       PAUSED       ");
            break;
        case 6:
            printf("  --- Controls ---  ");
            break;
        case 7:
            printf("   [z, c] : Rotate  ");
            break;
        case 8:
            printf(" [l, r arrow] : Move");
            break;
        case 10:
            printf(" [down arrow]       ");
            break;
        case 11:
            printf("        : SoftDrop  ");
            break;
        case 12:
            printf(" [up arrow]         ");
            break;
        case 13:
            printf("        : HardDrop  ");
            break;
        case 15:
            printf("[x]:hold unavailable");
            break;
        case 17:
            printf("    press  \033[32m[Esc]\033[m    ");
            break;
        case 18:
            printf("    to  \033[32mCONTINUE\033[m    ");
            break;
        case 21:
            printf("    press  \033[31mENTER\033[m    ");
            break;
        case 22:
            printf("      to \033[31mEscape\033[m     ");
            break;
        default:
            printf("                    ");
            break;
    }
}

int pauseMenu(void)
{
    int ANIMATION_STEP_INTERVAL = 20;
    int animation_start = clock();
    int animation_time = clock() - animation_start;
    int animation_step = animation_time / ANIMATION_STEP_INTERVAL;
    int key_input;

    while (animation_step <= row)
    {
        if (kbhit())
        {
            if (getch() == 0x1b)
                return 0;
        }
        animation_time = clock() - animation_start;
        animation_step = animation_time / ANIMATION_STEP_INTERVAL;

        printf("\n");
        for (int y=0; y<row; y++)
        {
            renderLeftSide(y);
            if (y < animation_step)
                printPauseMenu(y);
            else
            {
            for (int x=0; x<10; x++)
                printColoredBlock(main_grid[y][x]);
            }
            switch (y)
            {
                case 1:
                    printf("##=====next=====##");
                    break;
                default:
                    printf("##              ##");
                    break;
            }
            printf("\n");
        }
        printf("######################################################\n");
        printf("\n\n\n");
        printf("\033[10D\033[%dA", row+5);
    }

    int respond = 0;
    while (respond == 0)
    {
        if (kbhit())
        {
            key_input = getch();
            switch (key_input)
            {
                case 0x1b:
                    respond = 1;
                    break;
                case 0x0d:
                    return 1;
                    break;
            }
        }
    }

    animation_start = clock();
    animation_step = 0;

    while (animation_step <= row)
    {
        animation_time = clock() - animation_start;
        animation_step = animation_time / ANIMATION_STEP_INTERVAL;

        printf("\n");
        for (int y=0; y<row; y++)
        {
            renderLeftSide(y);
            if (y < animation_step)
            {
            for (int x=0; x<10; x++)
                printColoredBlock(main_grid[y][x]);
            }
            else
                printPauseMenu(y);
            switch (y)
            {
                case 1:
                    printf("##=====next=====##");
                    break;
                default:
                    printf("##              ##");
                    break;
            }
            printf("\n");
        }
        printf("######################################################\n");
        printf("\n\n\n");
        printf("\033[10D\033[%dA", row+5);
    }
    return 0;
}



void hideConsoleCursor(void)
{
    BOOL bRtn;
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cci;
    SMALL_RECT rctWindowRect = {0,0,55,35};
    COORD dwCoord = {56,36};

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cci);
    bRtn = SetConsoleScreenBufferSize(hOut, dwCoord);
    bRtn = SetConsoleWindowInfo(hOut,TRUE,&rctWindowRect);
    return;
}

void showConsoleCursor(void)
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO cci;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hOut, &cci);
    cci.bVisible = TRUE;
    SetConsoleCursorInfo(hOut, &cci);
    return;
}

void moveCursor(int vertical, int horizontal)
{
    switch (vertical)
    {
        case 0:
            break;
        case -32768 ... -1:
            printf("\033[%dA", 0 - vertical);
            break;
        case 1 ... 32767:
            printf("\033[%dB", vertical);
            break;
    }

    switch (horizontal)
    {
        case 0:
            break;
        case -32768 ... -1:
            printf("\033[%dD", 0 - horizontal);
            break;
        case 1 ... 32767:
            printf("\033[%dC", horizontal);
            break;
    }
    return;
}

void printColoredBlock(int block_color)
{
    switch (block_color)
    {
        case 0:
            printf("\033[40m..\033[m");
            break;
        case 8:
            printf("\033[40m  \033[m");
        default:
            printf("\033[%dm  \033[m", block_color+40);
            break;
    }
    return;
}

void printSingleBrick(int *cordinates, int brick_type)
{
    if (brick_type >= 8)
    {
        return;
    }
    moveCursor(cordinates[1], cordinates[0] << 1);
    printColoredBlock(brick_type);
    for (int i=1; i<4; i++)
    {
        moveCursor(cordinates[(i << 1) + 1] - cordinates[((i-1) << 1) + 1],  (cordinates[i << 1] - cordinates[(i-1) << 1] - 1) << 1);
        printColoredBlock(brick_type);
    }
    moveCursor(0 - cordinates[7], (0 - cordinates[6] - 1) << 1);
    return;
}

int last_upcoming_bricks[5];

void initRenderGame(void)
{
    memcpy(last_upcoming_bricks, upcoming_bricks, sizeof(upcoming_bricks));
    return;
}

void print_next_brick(int brick_index)
{
    if (!areSameArray(last_upcoming_bricks, upcoming_bricks, sizeof(upcoming_bricks) / sizeof(int)))
        printf("              \033[14D");
    printf("   ");
    printSingleBrick(BRICKS_AND_ROTATIONS_AND_BLOCK_POSITIONS[upcoming_bricks[brick_index]-1][0], upcoming_bricks[brick_index]);
}

void renderLeftSide(int y)
{
    switch (y)
    {
        case 1:
            printf("=====score====##");
            break;
        case 3:
            printf("%14ld##",score);
            break;
        case 5:
            printf("=====lines====##");
            break;
        case 7:
            printf("%14ld##",lines);
            break;
        case 9:
            printf("=====time=====##");
            break;
        case 11:
            printf("%2d:%2d:%2d.%3d  ##", game_time/3600000, (game_time%3600000/60000), (game_time%60000)/1000, game_time%1000);
            break;
        case 13:
            printf("=====hold=====##");
            break;
        case 14:
            printf("-             ##");
            break;
        case 19:
            printf("==============##");
            break;
        default:
            printf("              ##");
            break;
    }

}

void renderRightSide(int y)
{
    printf("##\033[14C##\033[16D");
    switch (y)
    {
        case 1:
            printf("=====next=====");
            break;
        case 2:
            print_next_brick(0);
            break;
        case 6:
            printf("==============");
            break;
        case 7:
            print_next_brick(1);
            break;
        case 11:
            printf("==============");
            break;
        case 12:
            print_next_brick(2);
            break;
        case 16:
            printf("==============");
            break;
        case 17:
            print_next_brick(3);
            break;
        default:
            if (!areSameArray(last_upcoming_bricks, upcoming_bricks, sizeof(upcoming_bricks) / sizeof(int)))
                printf("              ");
            break;
    }
    printf("\n");
}

void renderGame(void)
{
    printf("\n");
    for (int i=0; i<(row+5); i++)
        printf("\n");
    printf("\033[%dA", row+5);
    for (int y=0; y<row; y++)
    {
        renderLeftSide(y);
        for (int x=0; x<10; x++)
        {
            printColoredBlock(main_grid[y][x]);
        }
        renderRightSide(y);
    }
    printf("######################################################\n");
    printf("\n\n\n");
    printf("\033[10D\033[%dA", row+5);

    memcpy(last_upcoming_bricks, upcoming_bricks, sizeof(upcoming_bricks));

}



