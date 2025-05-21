//
//  prg.cl
//  red1
//
//  Created by toby on 12.06.24.
//


//init
kernel void vec_ini(global float *uu)
{
    int i = get_global_id(0);
    
    uu[i] = i;

    return;
}


//sum in place
kernel void vec_sum(global float *uu,
                    const  int   n)
{
    int i = get_global_id(0);
    int m = get_global_size(0);

    printf("%d %d %d %f %f\n",i, n, m, uu[i], uu[m+i]);
    
    if((m+i)<n)
    {
        uu[i] += uu[m+i];
    }
      
    return;
}
