/* Include */

#include <unistd.h>
#include <term.h>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <chrono>
#include <thread>
#include <list>
#include <cmath>
/* Defines */
#define PI          3.14159265358979323846
#define WIDTH       80         /* Screen width */
#define HEIGHT      40         /* Screen height */
const char palette[] = ".:;~=#OB8%&";

using namespace std::chrono_literals;

constexpr std::chrono::nanoseconds timestep(400ms);

/* Function */


void gotoxy(short x ,short y)
{
    printf("%c[%d;%df", 0x1B, y, x);
}

void drawCircle(auto &canvas, int origin[], auto rad, char color){
    for (int yi=0;yi<HEIGHT;yi++){
        for (int xi=0; xi<WIDTH;xi++){
            int t = origin[0];
            int tt = origin[1];
            float wider = float(tt) / float(t);
            double distance = sqrt(pow(float(xi-origin[0]) * wider , 2) + pow(float(yi-origin[1]), 2));
            if (distance <= rad){
                canvas[yi][xi] = color;
            }
            else{
                canvas[yi][xi] = '8';
            }
        }
    }
}

int main() {
    int ORIGIN[2] = {static_cast<int>(WIDTH / 2), static_cast<int>(HEIGHT /2)};
    char canvas[HEIGHT][WIDTH];

    /* time tracking variables */
    std::chrono::nanoseconds lag(0ns);
    std::chrono::system_clock::time_point time_start;
    std::chrono::system_clock::time_point time_end;

    char plt[HEIGHT * WIDTH + HEIGHT -2] = {'-'};

    int n = 0;
    int p_size = int(std::size(palette));
    printf("\x1b[2J");
    int N = 10;
    while (n<=N){
        time_start = std::chrono::high_resolution_clock::now();
        ;
        drawCircle(canvas, ORIGIN, 5.0, n > 0 ? palette[p_size % n] : palette[1]);
        int p = 0;
        for (auto &canva : canvas) {
            for (char j : canva) {
                plt[p++] = j;
            }
            plt[p++] = 10;
        }
        puts(plt);

        time_end = std::chrono::high_resolution_clock::now();;
        lag = std::chrono::duration_cast<std::chrono::nanoseconds>(time_start - time_end);
        if (lag < timestep) {
            auto sleep_duration = (timestep - lag);
            std::this_thread::sleep_for(sleep_duration);
        }
        n++;
        if (n < N){
            continue;
        }
        else {
            gotoxy(0, HEIGHT);
        }


    }
}