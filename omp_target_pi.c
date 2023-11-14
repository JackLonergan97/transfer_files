#include <omp.h>
#include <stdio.h>
#define NBIN 1000000
#define NTMS 12
#define NTRD 96

int main() {
	float step,sum=0.0,pi;
	float sum_teams[NTMS];
	step = 1.0/(float)NBIN;
        for (int j=0; j<NTMS; j++) sumteams[j] = 0.0;
        step = 1.0/(float)NBIN;

	#pragma omp target teams map(step,sum_teams) num_teams(NTMS)
	{
            #pragma omp distribute
            for (int j=0; j<NTMS; j++) {
                long long ibgn = NBIN/NTMS*j;
                long long iend = NBIN/NTMS*(j+1);
                if (j == NTMS-1) iend = NBIN;
                # pragma omp parallel for reduction(+:sum_teams[j]) num_threads(NTRD)
                for (long long i=ibgn; i<iend; i++) {
                    float x = (i+0.5)*step;
                    sum_teams[j] += 4.0/(1.0+x*x);
                }
            }
	}
        for (int j=0; j<NTMS; j++) sum += sum_teams[j];
	
	pi = sum*step;
	printf("PI = %f\n",pi);
	return 0;
}
