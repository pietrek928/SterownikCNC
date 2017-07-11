void RCC_Conf(void)
{
    ErrorStatus HSEStartUpStatus;
    // Trzeba to wchuj wyzerowac
    RCC_DeInit();
    // Dawaj korwa HSE
    RCC_HSEConfig(RCC_HSE_ON);
    //wait for hse
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        RCC_HCLKCongig(RCC_SYSCLK_Div1);
        RCC_PCLK2Config(RCC_HCLK_Div1);
        RCC_PCLK1Congif(RCC_HCLK_Div2);
        //PLLCLK = 8MHz * 9 =72MHz
        RCC_PLLConfig(RCC_PLLSource_HSI_Div1, RCC_PLLMul_9);
        RCC_PLLCmd(ENABLE);
        // PLL ready?
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
        //RCC nakorwia sygnalem zegarwoym
        RCC_SYSCLKCongig(RCC_SYSCLKSource_PLLCLK);

        while(RCC_GetSYSCLKSource() != 0x08);
    }
}

