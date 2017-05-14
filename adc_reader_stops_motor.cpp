int main(){
    init();
    int input;
    input = 0;
    int adc_reading;
    while (input <= 600){
        adc_reading = read_analog(0);
        input = adc_reading;
        set_motor(1, 254);
    }
    set_motor(1,0);
}
