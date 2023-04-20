#include <stdio.h>
#include <stdlib.h>

struct coordinates
{
    int degree;
    int minute;
    int second;
};
struct position
{   
    struct coordinates latitude ;
    struct coordinates longitude;
};
struct fig
{ 
    struct  position apex1;
    struct  position apex2;
    struct  position apex3;
};  


void input_ship (int N, struct position * ship)
{
    if (N > 50)
        return;
    else 
    {
        for (int i = 0; i < N; ++i) 
        {
            int tmp_scan = 0;
            for (int j = 0; j < 6; ++j) 
            {
                scanf ("%d", &tmp_scan);
                if (j == 0) 
                {
                    if (tmp_scan < 0 || tmp_scan > 90)
                        return;
                }
                if (j == 3) 
                {
                    if (tmp_scan < 0 || tmp_scan > 180)
                        return;
                }

                else if (j == 1 || j == 4) 
                {
                    if (tmp_scan < 0 || tmp_scan > 60)
                        return;
                }

                else if (j == 2 || j == 5) 
                {
                    if (tmp_scan < 0 || tmp_scan > 60)
                        return;
                }

                *((int*)(&ship[i]) + j) = tmp_scan;
            }
        }
    }
}

void input_triangle (struct fig * triangle) 
{
    for (int i = 0; i < 3; ++i) 
    {
        int tmp_scan = 0;
        for (int j = 0; j < 6; ++j) 
        {
            scanf ("%d", &tmp_scan);
            if (j == 0) 
            {
                if (tmp_scan < 0 || tmp_scan > 90)
                    return;
            }
            if (j == 3) 
            {
                if (tmp_scan < 0 || tmp_scan > 180)
                    return;
            }
            else if (j == 1 || j == 4) 
            {
                if (tmp_scan < 0 || tmp_scan > 60)
                    return;
            }
            else if (j == 2 || j == 5) 
            {
                if (tmp_scan < 0 || tmp_scan > 60)
                    return;
            }

            *((int*)(triangle) + j + i * 6) = tmp_scan;
        }
    }
}

struct position input_port() 
{
    struct position pt = {};
    struct position ret = {};

    for (int j = 0; j < 6; ++j) 
    {
        int tmp_scan = 0;
        scanf ("%d", &tmp_scan);
        if (j == 0 || j == 3) 
        {
            if (tmp_scan < 0 || tmp_scan > 90) 
            {
                return ret;
            }
        }
        else if (j == 1 || j == 4) 
        {
            if (tmp_scan < 0 || tmp_scan > 180) 
            {
                return ret;
            }
        }
        else if (j == 2 || j == 5) 
        {
            if (tmp_scan < 0 || tmp_scan > 60)
            {
                return ret;
            }
        }

        *((int*)(&pt) + j) = tmp_scan;
    }

    return pt;
}

void matrix_of_slopes (int N, struct position *ship, struct fig triangle, struct position port, float (*slopes)[4])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<4; j++)
        {
           switch (j)
           {
               case 0:
                slopes [i][j] = (float)((triangle.apex1.latitude.degree*3600+triangle.apex1.latitude.minute*60+triangle.apex1.latitude.second) - (ship[i].latitude.degree*3600 + ship[i].latitude.minute*60 + ship[i].latitude.second))/((triangle.apex1.longitude.degree*3600+triangle.apex1.longitude.minute*60+triangle.apex1.longitude.second) - (ship[i].longitude.degree*3600 + ship[i].longitude.minute*60 + ship[i].longitude.second));
                break;

               case 1:
                slopes [i][j] = (float)((triangle.apex2.latitude.degree*3600+triangle.apex2.latitude.minute*60+triangle.apex2.latitude.second) - (ship[i].latitude.degree*3600 + ship[i].latitude.minute*60 + ship[i].latitude.second))/((triangle.apex2.longitude.degree*3600+triangle.apex2.longitude.minute*60+triangle.apex2.longitude.second) - (ship[i].longitude.degree*3600 + ship[i].longitude.minute*60 + ship[i].longitude.second));
                break;

               case 2:
                slopes [i][j] = (float)((triangle.apex3.latitude.degree*3600+triangle.apex3.latitude.minute*60+triangle.apex3.latitude.second) - (ship[i].latitude.degree*3600 + ship[i].latitude.minute*60 + ship[i].latitude.second))/((triangle.apex3.longitude.degree*3600+triangle.apex3.longitude.minute*60+triangle.apex3.longitude.second) - (ship[i].longitude.degree*3600 + ship[i].longitude.minute*60 + ship[i].longitude.second));
                break;

               case 3:
                slopes [i][j] = (float)((port.latitude.degree*3600+port.latitude.minute*60+port.latitude.second) - (ship[i].latitude.degree*3600 + ship[i].latitude.minute*60 + ship[i].latitude.second))/((port.longitude.degree*3600+port.longitude.minute*60+port.longitude.second) - (ship[i].longitude.degree*3600 + ship[i].longitude.minute*60 + ship[i].longitude.second));
                break;
           }

           printf ("%lg ", slopes [i][j]);

        }

        printf("\n");
    }

}

void danger_identification (int N, float (*slopes)[4], int *danger)
{
    int i = 0, j = 0;
    float max = 0, min = 0;
    for (i = 0; i < N; i++)
    {
        max = slopes[i][0];
        for (j = 1; j < 3; j++)
        {
            if (slopes[i][j] > max)
                max = slopes[i][j];
        }
        min = slopes[i][0];
        for (j = 1; j < 3; j++)
        {
            if (slopes[i][j] < min)
                min = slopes[i][j];
        }
        if (slopes[i][3] >= min && slopes[i][3] <= max)
        {
            danger[i] = 1;
        }
        else
            danger[i] = 0;
    }
}

void danger_signal (int N, int * danger)
{
	puts ("Ship index\tDanger");
	int i;
	for (i = 0; i < N; i++)
	{
		while (getchar () != '\n')
			continue;
		printf ("%d\t", i + 1);
		danger [i] ? printf ("YES\a") : printf ("NO");
	}
}

int main()
{
    struct position ship[50];
    struct fig triangle;
    struct position port;
    float slopes[50][4] = {};
    int  danger[50] = {};
    int N = 0;

    printf("Enter number of ships: ");
    scanf("%d", &N);

    input_port();
    input_ship(N, ship);
    input_triangle(&triangle);
    matrix_of_slopes(N, ship, triangle, port, slopes);
    danger_identification(N, slopes, danger);
    danger_signal(N, danger);

    return 1;
}
