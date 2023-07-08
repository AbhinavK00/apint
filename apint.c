#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static void apint_adder(const char* apint1, const char* apint2, char* res);
static char* apint_differ(const char* apint1, const char* apint2);
static void apint_multy(const char* apint1, const char* apint2, char* res);
static char* max(char* sum, char* curr);
static void merge(char **arr, int l, int m, int r);
static int isZero(const char* apint);
int apint_compare(const char* apint1, const char* apint2);
static char* removeLeadZero(char* apint);	
static char* removeLeadZero(char* res){

	int nonz = 0, newlen =0,i = 0;
	for(nonz = 0; nonz < strlen(res); nonz++){
		if(res[nonz] != 48)
			break;	
	}
	if(nonz == 0)
		return res;
	newlen = strlen(res) - nonz;
	for(i = 0; i < newlen; i++)
		res[i] = res[i+nonz];
	res[i] = '\0';
	if(res[0] == '\0'){
		free(res);
		res = (char*)calloc(2,sizeof(char));
		res[0] = 48;
		res[1] = '\0';	
	}
	return res;

}
static void apint_adder(const char* apint1, const char* apint2, char* res){
	int l1 = strlen(apint1)-1;
	int l2 = strlen(apint2)-1;
	int sum = 0, carry = 0,k = l1+1;
	for(int i = 0; i <= k;i++)
		res[i] = '0';
	while(l2>=0){
		sum = apint1[l1] + apint2[l2] + carry - 96;
		res[k] = 48 + sum%10;
		carry = sum/10;
		--l1;--l2;--k;		
	}
	while(l1>=0){
		sum = apint1[l1]+carry-48;
		res[k] = 48 + sum%10;
		carry = sum/10;
		--l1;--k;		
	}
	if(carry){
		res[k] = 48 + carry;
	}
	
}
char* apint_add(const char* apint1, const char* apint2){
	int bigger = apint_compare(apint1,apint2);
	if(bigger == -1){
		char* res = (char*)calloc(strlen(apint2)+2,sizeof(char));
		apint_adder(apint2, apint1, res);
		return removeLeadZero(res);
	}
	char* res = (char*)calloc(strlen(apint1)+2,sizeof(char));
	apint_adder(apint1, apint2, res);
	return removeLeadZero(res);
}
int apint_compare(const char* apint1, const char* apint2){
	int p1 = strlen(apint1)-1;
	int p2 = strlen(apint2)-1;
	int diff = 0, bigger = 0;
	int i =0;
	if(p1 < p2)
		return -1;
	if(p1 == p2){
		bigger = 0;
		do{
			diff = apint1[i] - apint2[i];
			if(diff > 0){
				bigger = 1;
			}else if(diff < 0){
				bigger = -1;
			}++i;
		}while(diff == 0 && i<=p1 && i <= p2);
		return bigger;
	}
	return 1;	
}
static char* apint_differ(const char* apint1, const char* apint2){
	int l1 = strlen(apint1)-1;
	int l2 = strlen(apint2)-1;
	int top = 0,bottom = 0,k = l1,i;
	int taken = 0;
	char* res = (char*)calloc(k+2,sizeof(char));
	for(i = 0; i <= k;i++)
		res[i] = 48;
	res[i] = '\0';
	while(l2>= 0){
		top = apint1[l1]-48;
		bottom = apint2[l2]-48;
		if(taken > 0){
			if(taken == 1){
				top -=1;
			}else{	
				top = 9 + apint1[l1]-48 ;
			}
			--taken;		
		}
		if(top < bottom){
			do{
				++taken;
			}while(apint1[l1-taken] == 48 && (l1-taken) > 0);
			top +=10;		
		}
		
		res[k] = 48+ top - bottom;
		--l1;--l2;--k;
	}
	while(l1>=0){
		if(taken >  0){
			res[k] = apint1[l1]-1; 
			if(apint1[l1] == 48)
				res[k] = 57;
			--taken;
		}else{
			res[k] = apint1[l1];		
		}
		--l1;--k;		
	}
	return res;
}
char* apint_diff(const char* apint1, const char* apint2){
	int bigger = apint_compare(apint1,apint2);
	if(bigger == -1){
		char* res = apint_differ(apint2, apint1);
		return removeLeadZero(res);
	}
	char* res = apint_differ(apint1, apint2);
	return removeLeadZero(res);
}
static int isZero(const char* apint){
	int i =0, len = strlen(apint);
	while(i<len){
		if(apint[i] == 48)
			++i;
		else
			break;		
	}
	if(apint[i] == '\0')
		return 1;
	return 0;
}
static void apint_multy(const char* apint1, const char* apint2, char* res){
	int l1 = strlen(apint1);
	int l2 = strlen(apint2);
	int sum = 0, carry = 0;
	int l3 = l1+l2;
	int ptr1 = 1;
	int ptr2;
	int i;
	for(i = 0; i < l3; i++){
		res[i] = '0';		
	}
	for(i = l2-1; i >= 0; i--){
		sum = 0;
		carry = 0;
		ptr2 = l3-ptr1;
		for(int j = l1-1; j >=0; j--){
			sum = (apint1[j]-'0')*(apint2[i]-'0') + (res[ptr2]-'0')+carry;
			res[ptr2] = 48+sum%10;
			carry = sum/10;
			--ptr2;	
		}
		if(carry){
			res[ptr2] += carry;		
		}
		++ptr1;		
	}
}
char* apint_multiply(const char* apint1, const char* apint2){
			
	if(!isZero(apint1) && !isZero(apint2)){
		int bigger = apint_compare(apint1,apint2);
		char* res = (char*)calloc(strlen(apint1)+strlen(apint2)+1,sizeof(char));
		if(bigger>=0){
			apint_multy(apint1, apint2, res);
		}else{
			apint_multy(apint2, apint1, res);
		}
		return removeLeadZero(res);
	}
	char* res = (char*)malloc(2*sizeof(char));
	strcpy(res,"0");
	return res;
}

char* apint_mod(const char* apint1, const char* apint2){
	int comp = apint_compare(apint1,apint2);
	int l1 = strlen(apint1);
	int l2 = strlen(apint2);
	int i;	
	if(isZero(apint1) || comp == 0){
		char* res = (char*)calloc(2,sizeof(char));
		strcpy(res,"0");
		return res;
	}
	if(comp == -1){	
		char* res = (char*)calloc(l1+1,sizeof(char));
		strcpy(res,apint1);
		return res;
	}
	int diff = l1-l2;
	if(apint1[0] <= apint2[0])
		--diff;
	if(diff == 0){
		char* temp = apint_diff(apint1,apint2);
		char* t2 = temp;
		char* res = apint_mod(temp, apint2);
		free(t2);
		return res;
	}
	char* ni1 = (char*)malloc(sizeof(char)*(l1+1));
	strcpy(ni1, apint1);
	char* ni2 = (char*)malloc(sizeof(char)*(l2+diff+2));
	for(i = 0; i < l2; i++)
		ni2[i] = apint2[i];
	for(i = 0; i < diff; i++)
		ni2[l2+i] = 48;
	ni2[l2+i] = '\0';
	while(apint_compare(ni1,ni2) >0){
		char* temp = apint_diff(ni1,ni2);
		char* t2 = ni1;
		ni1 = temp;
		free(t2);
	}
	free(ni2);
	if(apint_compare(ni1,apint2) <= 0)
		return ni1;
	char* temp = ni1;
	char* res = apint_mod(ni1,apint2);
	free(temp);
	return res;
}

char* apint_pow(const char* apint1, unsigned int n){
	if(isZero(apint1)){
		char* res = (char*)malloc(sizeof(char)*2);
		strcpy(res,"0");
		return res;	
	}
	char* res = (char*)malloc(sizeof(char)*2);
	strcpy(res,"1");
	char* x = (char*)malloc(sizeof(char)*(strlen(apint1)+1));
	strcpy(x,apint1);
	char* temp;
	while(n > 0){
		if(n & 1){
			temp = apint_multiply(res,x);
			free(res);
			res = temp;		
		}	
		n = n >> 1;
		temp = apint_multiply(x,x);
		free(x);
		x = temp;
	}
	free(x);
	return res;
}

char* apint_gcd(const char* apint1, const char* apint2){
	if(strcmp(apint1,"0")==0 && strcmp(apint2,"0")==0){
		char* res = (char*)calloc(2,sizeof(char));
		res[0] = '0';
		res[1] = '\0';	
		return res;
	}
	if(strcmp(apint1,"0")==0){
		char* res = (char*)calloc(strlen(apint2)+1,sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(apint2);i++)
			res[i] = apint2[i];
		res[i] = '\0';	
		return res;
	}
	if(strcmp(apint2,"0") == 0){
		char* res = (char*)calloc(strlen(apint1)+1,sizeof(char));
		int i = 0;		
		for(i = 0; i < strlen(apint1);i++)
			res[i] = apint1[i];
		res[i] = '\0';	
		return res;	
	}
	char* temp = apint_mod(apint1, apint2);
	char* res =  apint_gcd(apint2, temp);
	free(temp);
	return res;	
}

char* apint_fibonacci(unsigned int n){
	unsigned int i;	
	char* res1 = (char*)malloc(2 * sizeof(char));
	strcpy(res1,"0");
	if(n==0)
		return res1;
	char* res2 = (char*)malloc(2 * sizeof(char));

	strcpy(res2,"1");
	char* temp = NULL;
	for(i = 2; i <= n; i++){
		temp = apint_add(res1,res2);
		free(res1);
		res1 = res2;
		res2 = temp;
	}
	free(res1);
	return res2;
}
char* apint_factorial(unsigned int n){
	char* res = (char*)calloc(2,sizeof(char));
	strcpy(res,"1");	
	if(n == 0 || n== 1){
		return res;
	}
	char* num = (char*)calloc(2,sizeof(char));
	char* copy = NULL;
	strcpy(num,"1");
	unsigned int i = 2;
	while(i <= n){
		copy = apint_add(num,"1");
		free(num);
		num = copy;
		//printf("%s %s\n",num,res);
		copy = apint_multiply(num,res);
		free(res);
		res = copy;
		++i;	
	}
	free(num);
	return removeLeadZero(res);
}

char* apint_bincoeff(unsigned int n, unsigned int k){
	unsigned int i = 0;
	unsigned int j = 0;
	if(k > (n-k))
		k = n-k;
	char** dp = (char**)malloc(sizeof(char)*(k+1));
	dp[0] = (char*)malloc(2*sizeof(char));

	strcpy(dp[0],"1");
	
	for(i = 1; i <= k; i++){
		dp[i] = (char*)malloc(2*sizeof(char));
		strcpy(dp[i],"0");	
	}
	char* temp;
	for(i = 1; i <= n;i++){
		for(j = (i > k)?k:i; j > 0; j--){
			temp = apint_add(dp[j],dp[j-1]);
			free(dp[j]);
			dp[j] = temp;	
		}	
	}
	char* res = (char*)malloc(sizeof(char)*(strlen(dp[k])+1));
	strcpy(res,dp[k]);
	for(i = 0; i <= k; i++){
		free(dp[i]);
	}
	free(dp);
	return res;	
	
}

int apint_max(char **arr, int n){
	int min = 0,i;
	for(i = 1; i < n;i++){
		if(apint_compare(arr[min],arr[i]) < 0){
			min = i;		
		}		
	}
	return min;
}
int apint_min(char **arr, int n){
	int min = 0,i;
	for(i = 1; i < n; i++){
		if(apint_compare(arr[min],arr[i]) > 0){
			min = i;	
		}		
	}
	return min;
}
int apint_search(char **arr, int n, const char* key){
	int index =-1;	
	for(int i = 0; i< n; i++){
		if(apint_compare(arr[i],key) == 0){
			index = i;
			break;		
		}	
	}
	return index;
}
int apint_binsearch(char **arr, int n, const char* key){
	int lo = 0, hi = n-1;
	int mid = -1, comp = 0;
	while(lo <= hi){
		mid =lo + (hi - lo)/2; 
		comp = apint_compare(arr[mid],key);
		if(comp == 0){
			return mid;		
		}
		if(comp == 1){
			hi = mid-1;		
		}
		else{
			lo = mid+1;				
		}
	}
	return -1;
}

static void merge(char **arr, int l, int m, int r){ 
	int i, j, k; 
	int n1 = m - l + 1; 
	int n2 =  r - m; 
	char** left = (char**)malloc(sizeof(char)*n1);
	char** right = (char**)malloc(sizeof(char)*n2);
	for (i = 0; i < n1; i++){
		left[i] = (char*)malloc(sizeof(char)*(strlen(arr[l+i])+1)); 
		strcpy(left[i],arr[l+i]);
	} 
	for (j = 0; j < n2; j++){ 
		right[j] = (char*)malloc(sizeof(char)*(strlen(arr[m + 1+ j])+1)); 
		strcpy(right[j],arr[m + 1+ j]);
	} 
	i = 0;j = 0;k = l; 
	while (i < n1 && j < n2){ 
		if(apint_compare(left[i],right[j]) <= 0){ 
			strcpy(arr[k],left[i]); 
			i++; 
        	}else{ 
            		strcpy(arr[k],right[j]); 
            		j++; 
        	} 
        	k++; 
    	} 
	while (i < n1){ 
        	strcpy(arr[k],left[i]); 
       		i++; 
        	k++; 
    	} 
	while (j < n2){
		strcpy(arr[k],right[j]); 
        	j++; 
        	k++; 
    	}
	for(i = 0; i < n1; i++)
		free(left[i]);
	free(left);
	for(i = 0; i < n2; i++)
		free(right[i]);
	free(right); 
} 
void apint_sort(char **arr, int n){
	int curr_size;
	int left_start;
	for(curr_size=1; curr_size<=n-1; curr_size = 2*curr_size){ 
		for (left_start=0; left_start<n-1; left_start += 2*curr_size){ 
			int mid = ((left_start + curr_size - 1) > n-1)?(n-1):(left_start + curr_size - 1); 
			int right_end = ((left_start + 2*curr_size - 1) > n-1)?(n-1):(left_start + 2*curr_size - 1); 
  			merge(arr, left_start, mid, right_end); 
		} 
	} 
}
static char* max(char* sum, char* curr){
	int comp = apint_compare(sum,curr);
	if(comp >=0){
		return sum;
	}
	free(sum);
	return curr;
}
char* coin_row_problem(char **arr, int n){
	if(n == 0){
		char* res = (char*)malloc(sizeof(char)*2);
		strcpy(res,"0");
		return res;
	}
	char* prev = (char*)malloc(sizeof(char)*2);
	strcpy(prev,"0");
	char* curr = (char*)malloc(sizeof(char)*(strlen(arr[0])+1));
	strcpy(curr,arr[0]);
	char* next;
	for(int i = 1; i < n;i++){
		next = max(apint_add(prev,arr[i]),curr);
		if(apint_compare(prev,curr) != 0){
			free(prev);
			prev = curr;
		}		
		curr = next;
	}
	if(apint_compare(prev,curr) != 0)
		free(prev);
	return curr;	
}

int main(){}
