CONTAINER Fsmdloader
{
    NAME Fsmdloader;
    
    GROUP
    {
        GROUP
        {
            NAME S_SCALEORIENTATION;
            DEFAULT 1;

            REAL SMD_LOADER_SCALE
            {
                MIN 0.01;
                MAX 100;
                STEP 0.1;
            }

            VECTOR SMD_LOADER_ROTATE { UNIT DEGREE; }
            BOOL SMD_LOADER_SWAPYZ {}
        }
    }
}