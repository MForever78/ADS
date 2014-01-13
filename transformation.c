#include "stdio.h"
#include "affine.h"
main()
{
	int driver=DETECT,mode,i;
	static double x1[]={0.0,10.0,80.0,100.0,0.0};
	static double y1[]={0.0,50.0,50.0,0.0,0.0};
	static double x2[5],y2[5],x3[5],y3[5],x4[5],y4[5];
	double x,xx,yy,r;
	initgraph(&driver,&mode,"");
	axis();

	for(i=0;i<=3;i++){
		line(scx(x1[i]),scy(y1[i]),scx(x1[i+1]),scy(y1[i+1]));
	}
	scale(2.0);
	
	for(i=0;i<=4;i++){
		x2[i]=affinex(x1[i],y1[i],1.0);
		y2[i]=affiney(x1[i],y1[i],1.0);
		delay(30000);
	}

	for(i=0;i<=3;i++){
		line(scx(x2[i]),scy(y2[i]),scx(x2[i+1]),scy(y2[i+1]));
	}

	r=60;
	rotate(r);
	for(i=0;i<=4;i++){
		x3[i]=affinex(x2[i],y2[i],1.0);
		y3[i]=affiney(x2[i],y2[i],1.0);
		delay(30000);
	}

	for(i=0;i<=3;i++){
		line(scx(x3[i]),scy(y3[i]),scx(x3[i+1]),scy(y3[i+1]));
	}

	palert::el(50.0,-150.0);
	for(i=0;i<=4;i++){
		x4[i]=affinex(x3[i],y3[i],1.0);
		y4[i]=affiney(x3[i],y3[i],1.0);
		delay(30000);
	}

	for(i=0;i<=3;i++){
		line(scx(x4[i]),scy(y4[i]),scx(x4[i+1]),scy(y4[i+1]));
	}

	getch();
	closegraph();
}