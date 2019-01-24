//By liposlt
//HP HPDL1414测试程序

#define HC595_DS  2
#define HC595_RCK 3
#define HC595_SCK 4
#define A0        5
#define A1        6
#define WR        7

#define HC595_DS_RESET    digitalWrite(HC595_DS, LOW)
#define HC595_DS_SET      digitalWrite(HC595_DS, HIGH)

#define HC595_ST_CP_RESET digitalWrite(HC595_RCK, LOW)    //RCK
#define HC595_ST_CP_SET   digitalWrite(HC595_RCK, HIGH)

#define HC595_SH_CP_RESET digitalWrite(HC595_SCK, LOW)    //SCK
#define HC595_SH_CP_SET   digitalWrite(HC595_SCK, HIGH)

void setup() {
  // put your setup code here, to run once:
  pinMode(HC595_DS, OUTPUT);
  pinMode(HC595_RCK, OUTPUT);
  pinMode(HC595_SCK, OUTPUT);
  pinMode(A1,  OUTPUT);
  pinMode(A0,  OUTPUT);
  pinMode(WR,  OUTPUT);

  digitalWrite(A1, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(WR, HIGH);

  HPDL_1414_WriteChar(3, 'A');
  HPDL_1414_WriteChar(2, 'B');
  HPDL_1414_WriteChar(1, 'C');
  HPDL_1414_WriteChar(0, 'D');
  delay(2000);
}
int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  if (i > 0x3f)
    i = 0;
  HPDL_1414_WriteChar(3, 0x20 + i);
  HPDL_1414_WriteChar(2, 0x21 + i);
  HPDL_1414_WriteChar(1, 0x22 + i);
  HPDL_1414_WriteChar(0, 0x23 + i);
  delay(500);
    i++;
}

void HPDL_1414_WriteChar(int pos, char chr)
{
  digitalWrite(A1, (pos & 2) >> 1);
  digitalWrite(A0, (pos & 1));
  digitalWrite(WR, LOW);

  HC595SendData(chr);
}

void HC595SendData(char data)
{
  int i = 0;
  for (i = 0; i < 8; i++)
  {
    if (data & 0x80)
      HC595_DS_SET;
    else
      HC595_DS_RESET;
    data <<= 1;
    HC595_SH_CP_SET;
    HC595_SH_CP_RESET;
  }
  HC595_ST_CP_SET;
  HC595_ST_CP_RESET;
}
