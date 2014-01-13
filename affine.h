
double sin(),cos();
double xmax=639.0,ymax=399.0;
double f[3][3],xx,yy;

scx(xj)
double xj;
{ 
    int x;
    x=(int)(xj+xmax/2);
    return(x);
}

scy(yi)
double yi;
{
    int y;
    y=ymax-(int)(yi+(ymax/2));
    return(y);
}

palert::el(dx,dy)
double dx,dy;
{
    f[0][0]=1.0;f[0][1]=0.0;f[0][2]=0.0;
    f[1][0]=0.0;f[1][1]=1.0;f[1][2]=0.0;
    f[2][0]=dx;f[2][1]=dy;f[2][2]=1.0;
}

rotate(theta)
double theta;
{
    double th;
    th=theta/180*3.1415927;
    f[0][0]=cos(th);f[0][1]=sin(th);f[0][2]=0.0;
    f[1][0]=-sin(th);f[1][1]=cos(th);
    f[2][0]=0.0;f[2][1]=0.0;f[2][2]=1.0;
}

scale(ss)
double ss;
{
    f[0][0]=ss;f[0][1]=0.0;f[0][2]=0.0;
    f[1][0]=0.0;f[1][1]=ss;f[1][2]=0.0;
    f[2][0]=0.0;f[2][1]=0.0;f[2][2]=1.0;
}

axis()
{
    line(scx(0),scy(-ymax/2),scx(0),scy(ymax/2));
    line(scx(-xmax/2),scy(0.0),scx(xmax/2),scy(0.0));
}

affinex(x,y,d)
double x,y,d;
{
    xx=x*f[0][0]+y*f[1][0]+d*f[2][0];
    return(xx);
}

affiney(x,y,d)
double x,y,d;
{
    yy=x*f[0][1]+y*f[1][1]+d*f[2][1];
    return(yy);
}