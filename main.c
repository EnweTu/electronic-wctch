#include <reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int
sbit dula=P3^6;
sbit wela=P3^7;
sbit key1=P3^0;
sbit key2=P3^1;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,
0x76,0x79,0x38,0x3f,0};
uchar hour,min,sec,year,month,day,al_hour,al_min;
uchar key_val,t0,t1,flag;
uint num;
void init();
int  key_scan();
void display_altime(uchar aa,uchar bb,uchar cc,uchar dd);
void display_time(uchar,uchar,uchar,uchar,uchar,uchar);
void display_data(uchar,uchar,uchar,uchar,uchar,uchar);
void display_timeset(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff);
void display_timeset_hour(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff);
void display_timeset_min(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff);
void display_timeset_sec(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff);
void delay(int x)
{
  int i,j;
  for(i=0;i<x;i++)
  	for(j=0;j<120;j++);//计数120次，约为1毫秒。
}
void main()
{
	init();
	while(1)
	{
		flag=0;
		key_val=0;
		display_time(hour/10,hour%10,min/10,min%10,sec/10,sec%10);
		if(key_scan()==1)
		{
			key_val=0;
			while(1)
			{
				display_data(year/10,year%10,month/10,month%10,day/10,day%10);
				if(key_scan()==1)
				{
					key_val=0;
					while(1)
					{
						display_altime(al_hour/10,al_hour%10,al_min/10,al_min%10);
						if(key_scan()==1)
						{
							key_val=0;
							break;
						}
					}
					break;
				}
			}
		}
		if(key_scan()==2)
		{
			uchar hour_s,min_s,sec_s;
			hour_s=hour;	min_s=min;	sec_s=sec;
			key_val=0;
			while(1)
			{
				display_timeset_hour(hour_s/10,hour_s%10,min_s/10,min_s%10,sec_s/10,sec_s%10);
				if(key_scan()==1)
				{
					key_val=0;
					hour_s++;
					if(hour_s==24)
						hour_s=0;
					flag=1;
				}
				if(flag==1&&key_scan()==2)
				{
					key_val=0;
					while(1)
					{
						display_timeset_min(hour_s/10,hour_s%10,min_s/10,min_s%10,sec_s/10,sec_s%10);
						if(key_scan()==1)
						{
							key_val=0;
							min_s++;
							if(min_s==60)
								min_s=0;
						}
						if(key_scan()==2)
						{
							key_val=0;
							while(1)
							{
								display_timeset_sec(hour_s/10,hour_s%10,min_s/10,min_s%10,sec_s/10,sec_s%10);
								if(key_scan()==1)
								{
									key_val=0;
									sec_s++;
									if (sec_s==60)
										sec_s=0;
								}
								if(key_scan()==2)
								{
									key_val=0;
									TR0=0;
									TH0=(65536-50000)/256;
									TL0=(65536-50000)%256;
									hour=hour_s;min=min_s;sec=sec_s;
									while(1)
									{
										display_timeset(hour/10,hour%10,min/10,min%10,sec/10,sec%10);
										if(key_scan()==1)
										{
											key_val=0;
											TR0=1;
											break;
										}
									}
									break;
								}
							}
							break;
						}
					}
					break;
				}
				if(key_scan()==2)
				{
					key_val=0;
					while(1)
					{
						display_timeset_hour(year/10,year%10,month/10,month%10,day/10,day%10);
						if(key_scan()==1)
						{
							key_val=0;
							year++;
							if(year==99)
								year=0;
							flag=1;
						}
						if(flag==1&&key_scan()==2)
						{
							key_val=0;
							while(1)
							{
								display_timeset_min(year/10,year%10,month/10,month%10,day/10,day%10);
								if(key_scan()==1)
								{
									key_val=0;
									month++;
									if(month==13)
										month=1;
								}
								if(key_scan()==2)
								{
									key_val=0;
									while(1)
									{
										display_timeset_sec(year/10,year%10,month/10,month%10,day/10,day%10);
										if(key_scan()==1)
										{
											key_val=0;
											day++;
											if (day==31)
												day=1;
										}
										if(key_scan()==2)
										{
											key_val=0;
											break;
										}
									}
									break;
								}
							}
							break;
						}
						if(key_scan()==2)
						{
							key_val=0;
							while(1)
							{
								display_timeset_hour(al_hour/10,al_hour%10,al_min/10,al_min%10,20,20);
								if(key_scan()==1)
								{
									key_val=0;
									al_hour++;
									if(al_hour==24)
										al_hour=0;
									flag=1;
								}
								if(flag==1&&key_scan()==2)
								{
									key_val=0;
									while(1)
									{
										display_timeset_min(al_hour/10,al_hour%10,al_min/10,al_min%10,20,20);
										if(key_scan()==1)
										{
											key_val=0;
											al_min++;
											if(al_min==60)
												al_min=0;
										}
										if(key_scan()==2)
										{
											key_val=0;
											break;
										}
									}
									break;
								}
								if(key_scan()==2)
								{
									key_val=0;
									break;
								}
							}
							break;
						}
					}
					break;
				}
			}
		}
	}
}
void init()
{
	num=1000; flag=0;
	hour=23;min=59;sec=55;
	year=16;month=12;day=31;
	TMOD=0x11;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	//TH1=(65536-50000)/256;
	//TL1=(65536-50000)%256;
	EA=1;
	ET0=1;
	//ET1=1;
	TR0=1;
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t0++;
	if(t0==20)
	{
		t0=0;
		sec++;
		if(sec==60)
		{
			sec=00;
			min++;
			if(min==60)
			{
				min=00;
				hour++;
				if(hour==24)
				{
					hour=00;
				}
			}
		}
	}

}
//void timer1() interrupt 3
//{
//	TH1=(65536-50000)/256;
//	TL1=(65536-50000)%256;
//	t1++;
//	if(t1%10==0)
//	{
//		P1=~P1;
//	}
//}

int key_scan()
{
	if(key1==0)
	{
		delay(5);
		if(key1==0)
			while(key1==0);
		delay(5);
		if(key1!=0)
			key_val=1;
	}
	
	if(key2==0)
	{
		delay(5);
		if(key2==0)
			while(key2==0);
		delay(5);
		if(key2!=0)
			key_val=2;
	}
	return key_val;
}

void display_time(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	uchar a;
	for(a=1;a<=5;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=0x40;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=0x40;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
	for(a=1;a<=20;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
}
void display_data(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=table[aa];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfd;
	wela=0;
	dula=1;
	P0=table[bb];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfb;
	wela=0;
	dula=1;
	P0=0x40;
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xf7;
	wela=0;
	dula=1;
	P0=table[cc];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[dd];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xdf;
	wela=0;
	dula=1;
	P0=0x40;
	dula=0;
	P0=0xff;
	delay(5);
	
	wela=1;
	P0=0xbf;
	wela=0;
	dula=1;
	P0=table[ee];
	dula=0;
	P0=0xff;
	delay(5);
	
	wela=1;
	P0=0x7f;
	wela=0;
	dula=1;
	P0=table[ff];
	dula=0;
	P0=0xff;
	delay(5);
}
void display_timeset_hour(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	uchar a;
	for(a=1;a<=10;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xfb;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xdf;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
	for(a=1;a<=15;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
}
void display_timeset_min(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	uchar a;
	for(a=1;a<=10;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xfb;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xdf;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
	for(a=1;a<=15;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
}
void display_timeset_sec(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	uchar a;
	for(a=1;a<=10;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xfb;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

//		wela=1;
//		P0=0xdf;
//		wela=0;
//		dula=1;
//		P0=0x40;
//		dula=0;
//		P0=0xff;
//		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
	}
	for(a=1;a<=15;a++)
	{
		wela=1;
		P0=0xfe;
		wela=0;
		dula=1;
		P0=table[aa];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfd;
		wela=0;
		dula=1;
		P0=table[bb];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xfb;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xf7;
		wela=0;
		dula=1;
		P0=table[cc];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xef;
		wela=0;
		dula=1;
		P0=table[dd];
		dula=0;
		P0=0xff;
		delay(5);

		wela=1;
		P0=0xdf;
		wela=0;
		dula=1;
		P0=0x00;
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0xbf;
		wela=0;
		dula=1;
		P0=table[ee];
		dula=0;
		P0=0xff;
		delay(5);
		
		wela=1;
		P0=0x7f;
		wela=0;
		dula=1;
		P0=table[ff];
		dula=0;
		P0=0xff;
		delay(5);
	}
}
void display_timeset(uchar aa,uchar bb,uchar cc,uchar dd,uchar ee,uchar ff)
{
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=table[aa];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfd;
	wela=0;
	dula=1;
	P0=table[bb];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfb;
	wela=0;
	dula=1;
	P0=0x40;
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xf7;
	wela=0;
	dula=1;
	P0=table[cc];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[dd];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xdf;
	wela=0;
	dula=1;
	P0=0x40;
	dula=0;
	P0=0xff;
	delay(5);
	
	wela=1;
	P0=0xbf;
	wela=0;
	dula=1;
	P0=table[ee];
	dula=0;
	P0=0xff;
	delay(5);
	
	wela=1;
	P0=0x7f;
	wela=0;
	dula=1;
	P0=table[ff];
	dula=0;
	P0=0xff;
	delay(5);
}
void display_altime(uchar aa,uchar bb,uchar cc,uchar dd)
{
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=table[aa];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfd;
	wela=0;
	dula=1;
	P0=table[bb];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfb;
	wela=0;
	dula=1;
	P0=0x00;
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xf7;
	wela=0;
	dula=1;
	P0=table[cc];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xef;
	wela=0;
	dula=1;
	P0=table[dd];
	dula=0;
	P0=0xff;
	delay(5);
}