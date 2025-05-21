//
//  prg.cl
//  red1
//
//  Created by toby on 12.06.24.
//


//init
kernel void vec_ini(global float *uu)
{
    int glb_pos = get_global_id(0);
    
    uu[glb_pos] = 1e0f; //glb_pos;

    return;
}


//sum in place
kernel void vec_sum(const  int      n,      //size uu
                    const  int      s,      //stride
                    global float    *uu)
{
    int glb_pos = get_global_id(0);
    int loc_pos = get_local_id(0);
//    int grp_pos = get_group_id(0);
    
//    //width
//    constant int w = 32;
//    
//    //buffer
//    local float uu_loc[w];
//    
//    //strided pos
//    int str_pos = s*glb_pos;
//    
//    //read (zero padded values)
//    uu_loc[loc_pos] = (str_pos<n)*uu[str_pos];
//    
//    //sync
//    mem_fence(CLK_LOCAL_MEM_FENCE);
//    
//    float usum = 0e0f;
//    
//    //reduce
//    for(int i=0; i<w; i++)
//    {
//        usum += uu_loc[i];
//    }
//    
//    //write all (for debug)
//    uu[str_pos] = (loc_pos==0)*usum;
//    
////    //write stride
////    if(loc_pos==0)
////    {
////        uu[str_pos] = usum;
////    }
//
////    printf("%2d %2d %2d %8.4f %2d %8.4f\n", n, loc_pos, glb_pos, uu_loc[loc_pos], str_pos, uu[str_pos]);
//    
    
    return;
}
