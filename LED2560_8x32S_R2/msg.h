char TxtAncs[] = {" ANCS - CUSTOM BUILT AUDIO / VISUAL - WWW.AUTOAV.Co.UK "};

/*
 * To change string via network... 2020.
 * memset(TxtAncs,0,sizeof TxtAncs);
   string.toCharArray(TxtAncs, string.length());
 */

 void scrollText(){
  lowTxt.SetFrameRate(1);
  if (lowTxt.UpdateText() == -1) { // if end of text
    int Size = 0;
    while (TxtAncs[Size] != '\0') Size++;
    lowTxt.SetText((unsigned char *)TxtAncs,Size);
  }
  else{
  FastLED.show();
  }

}
