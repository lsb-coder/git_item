int kthGrammar(int N,int K){
	int a = 2^(30-1);
	int str[30][a];
	str[0][0]=0;
	str[1][0]=0;str[1][1]=1;
	for(int i=2;i<30;i++){
		if(i%2!=0) {
			for(int j=0;j<2^(i-1)/2;j++)
				str[i][j]=str[i-1][j];
			int k = 2^(i-2)/2;
			for(int j=2^(i-1)-1;j>2^(i-1)*3/4;j--){
				str[i][j]=str[i-1][k];
				k++;
			int k = 2^(i-2)/2;
			for(int j=(2^(i-1)/2;j<2^(i-1)*3/4;j++){
				str[i][j]=str[i-1][k];
				k++;
			}
		}

		else {
			for(int j=0;j<2^(i-1)/2;j++)
				str[i][j]=str[i-1][j];
			int k = 0;
			for(int j=2^(i-1)-1;j>2^(i-1)/2;j--){
				str[i][j]=str[i-1][k];
				k++;
			}
		}

	}
	printf("%d",str[N-1][K-1]);
	return 0;
}
3:0110
4:01101001
5:0110100110010110
