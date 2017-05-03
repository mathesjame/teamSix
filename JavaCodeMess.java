import ecs100.*;
public class Bot
{
    private int x;
    private int y;
    private String name;
    private String Id;
    private static int idsofar = 1;
    private double size = 50;
    public Bot(String n, int xin, int yin)
    {
        y = yin;
        x = xin;
        name = n;
        Id = "Bot"+idsofar;
        idsofar++;
        draw();
    }
    private void draw(){
        UI.drawOval(x, y, size, size);
        UI.drawString(Id, x+(size*0.3), y+(size*0.7));
       
    }
    private void erase(){
        UI.eraseOval(x, y, size, size);
        UI.eraseString(Id, x+(size*0.3), y+(size*0.7));
       
    }
    public void jump(int yin)
    {
        erase();
        y=y+yin;
        draw();
    }
}
