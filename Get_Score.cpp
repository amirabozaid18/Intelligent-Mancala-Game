int Get_Score(int8_t state[])
{
    int CPU_Score = state[0]+state[1]+state[2]+state[3]+state[4]+ state[5]+ state[6];
    int HUMAN_Score = state[7]+ state[8] + state[9] + state[10] + state[11] + state[12] + state[13];
    int score = CPU_Score - HUMAN_Score;
    return score;
}