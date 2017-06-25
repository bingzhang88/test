#include<iostream>
#include<fstream>
#include<vector>
#include<stack>
#include<queue>
#include<math.h>
#include<string>
#include<algorithm>
using namespace std;
#define min(x,y) (x)>(y)?(y):(x)
struct TreeNode{
	int val;
	TreeNode * left;
	TreeNode * right;
	TreeNode(int x) {val=x;left=NULL;right=NULL;}
};
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
	val(x), next(NULL) {
}
};
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
class solution{

	public:
    TreeNode* reConstructBinaryTree1(int pre[],int startpre,int endpre,int vin[],int startvin,int endvin) {
		if(startpre > endpre || startvin > endvin)
		{
			return NULL;
		}
		TreeNode *root = new TreeNode(pre[startpre]);
		for(int i=startvin;i<=endvin;i++)
		{
			if(vin[i]==pre[startpre])
			{
				root->left=reConstructBinaryTree1(pre,startpre+1,startpre+(i-startvin),vin,startvin,i-1);
				root->right=reConstructBinaryTree1(pre,i-startvin+startpre+1,endpre,vin,i+1,endvin);
			}
		}
		return root;
    }

	TreeNode* reConstructBinaryTree2(int back[],int startback,int endback,int vin[],int startvin,int endvin) {
		if(startback > endback || startvin > endvin)
		{
			return NULL;
		}
		TreeNode *root = new TreeNode(back[endback]);
		for(int i=startvin;i<=endvin;i++)
		{
			if(vin[i]==back[endback])
			{
				root->left= reConstructBinaryTree2(back,startback,startback+(i-startvin)-1,vin,startvin,i-1);
				root->right=reConstructBinaryTree2(back,i-startvin+startback,endback-1,vin,i+1,endvin);
			}
		}
		return root;
    }


	void replaceSpace(char *str,int length) {
		char *s=new char[length];
		for(int i=0;i<length;i++)
		{
			s[i]=str[i];
		}
		int k=0;
		for(int i=0;i<length;i++)
		{
			if(s[i]==' ')
			{
				str[k]='%';
				str[++k]='2';
				str[++k]='0';
				k++;
			}
			else
			{
				str[k++]=s[i];
			}
		}	
	}

	void nodemirror(TreeNode *pRoot)
	{
		if(pRoot==NULL)
			return;
		TreeNode *temp;
		temp=pRoot->right;
		pRoot->right=pRoot->left;
		pRoot->left=temp;
		nodemirror(pRoot->left);
		nodemirror(pRoot->right);
	}

	void Mirror(TreeNode *pRoot) {
		nodemirror(pRoot);
    }

	vector<int> printMatrix(vector<vector<int> > matrix) {
		int n=matrix.size();
		int m=n;
		int count=0;
		vector<int> result;
		while(n>0)
		{
			if(n==1)
			{
				//cout<<matrix[(m-1)/2][(m-1)/2]<<" ";
				result.push_back(matrix[(m-1)/2][(m-1)/2]);
			}
			else
			{
				for(int i=count;i<count+n;i++)
					result.push_back(matrix[count][i]);
					//cout<<matrix[count][i]<<" ";

				for(int i=count+1;i<=m-1-count-1;i++)
					result.push_back(matrix[i][m-1-count]);
					//cout<<matrix[i][m-1-count]<<" ";


				for(int i=count+n-1;i>=count;i--)
					result.push_back(matrix[m-1-count][i]);
//					cout<<matrix[m-1-count][i]<<" ";

				for(int i=m-1-count-1;i>=count+1;i--)
					result.push_back(matrix[i][count]);
//					cout<<matrix[i][count]<<" ";
			}

			count++;
			n-=2;
		}
		return result;
    }


	bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        int num=pushV.size();
        stack<int>s;
        int index=0;
        for(int i=0;i<num;i++)
            {
            s.push(pushV[i]);
			while(!s.empty() && s.top()==popV[index])
                {
                index++;
                s.pop();
            }
        }
        return s.empty();
    }


	vector<int> PrintFromTopToBottom(TreeNode* root) {
		vector<int> result;
		queue<TreeNode*>q;
		if(root==NULL)
			return result;
		q.push(root);
		while(!q.empty())
		{
			TreeNode* temp=q.front();
			q.pop();
			result.push_back(temp->val);
			if(temp->left!=NULL)
				q.push(temp->left);
			if(temp->right!=NULL)
				q.push(temp->right);
		}
		return result;
    }

	
	vector<vector<int> >  result;
	vector<int> temp;
	vector<vector<int> > FindPath(TreeNode* root,int expectNumber) {
		
		if(root==NULL)
			return result;
		else
			findonepath(root,expectNumber);
		return result;

    }
	void findonepath(TreeNode *root,int expectNumber)
	{
		temp.push_back(root->val);
		if(root->left==NULL && root->right==NULL && expectNumber-root->val==0){
			
			result.push_back(temp);
		}
		if(root->left!=NULL) findonepath(root->left,expectNumber-root->val);
		if(root->right!=NULL) findonepath(root->right,expectNumber-root->val);
		temp.pop_back();
		
	}

	RandomListNode* Clone(RandomListNode* pHead)
    {
		if(pHead==NULL)
			return pHead;
        RandomListNode*temp=pHead;
		RandomListNode*temp_next;
        while(temp){
            temp_next=new RandomListNode(temp->label);
			temp_next->next=temp->next;
			temp->next=temp_next;
			temp=temp_next->next;
        }
		temp=pHead;
		while(temp){
			if(temp->random){
                temp->next->random=temp->random->next;
                
            }
			temp=temp->next->next;
        }
		temp=pHead->next;
		temp_next=pHead;
        RandomListNode*tmp;
		while(temp_next->next)
		{
            tmp=temp_next->next;
			temp_next->next=tmp->next;
			temp_next=tmp;
		}
        return temp;
    }


	ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
    	vector<ListNode*>vec;
        if(pListHead==NULL) return pListHead;
        while(pListHead)
            {
            vec.push_back(pListHead);
            pListHead=pListHead->next;
        }
        return *(vec.end()-k);
    }
	stack<TreeNode*> s;
	TreeNode* Convert(TreeNode* pRootOfTree)
    {
        if(pRootOfTree == NULL) return pRootOfTree;
		
        //pRootOfTree = ConvertNode(pRootOfTree);
		link_node(pRootOfTree);
		pRootOfTree = rebuild_list(s);
        //while(pRootOfTree->left) pRootOfTree = pRootOfTree->left;
        return pRootOfTree;
    }
	TreeNode* rebuild_list(stack<TreeNode*> &s)
	{
		TreeNode* curr;
		TreeNode* old;
		bool isfirst=true;
		while(!s.empty())
		{
			if(isfirst){
				isfirst=false;
				curr=s.top();
				old=curr;
				s.pop();
			}
			else
			{
				curr=s.top();
				curr->right=old;
				old->left=curr;
				old=curr;
				s.pop();
			}

		}
		return curr;
	}
	void link_node(TreeNode* root)
	{
		if(!root) return;
		link_node(root->left);
		s.push(root);
		link_node(root->right);
	}


    TreeNode* ConvertNode(TreeNode* root)
    {
		if(root == NULL) return root;
        if(root->left)
        {
            TreeNode *left = ConvertNode(root->left);
            while(left->right) left = left->right;
            left->right = root;
            root->left = left;
        }
         
        if(root->right)
        {
            TreeNode *right = ConvertNode(root->right);
            while(right->left) right = right->left;
            right->left = root;
            root->right = right;
        }
        return root;
    }

	vector<string> res;
	void p(string str,int index)
	{
		if(str.size()==0 || index<0)
			return ;
		if(index==str.size()-1)
			res.push_back(str);
		else
		{
			for(int i=index;i<str.size();i++)
			{
				if(i!=index && str[i]==str[index])
					continue;
				char temp;
				temp=str[i];
				str[i]=str[index];
				str[index]=temp;


				p(str,index+1);
			}
		}
		return;
	}
	vector<string> Permutation(string str) {
		p(str,0);
		return res;
    }


	int MoreThanHalfNum_Solution(vector<int> numbers) {
		sort(numbers.begin(),numbers.end());
		int l=numbers.size();
		int times=1;
		int temp=1;
		int max_num=numbers[0];
		int index=0;
		int max_times=1;
		for(int i=1;i<l;i++)
		{
			if(numbers[i]==numbers[i-1])
			{
				temp++;
			}
			else
			{
				if(temp>max_times)
				{
					max_times=temp;
					max_num=numbers[i-1];
				}
				//times.push_back(times);
				temp=1;
				
			}
		}
		if(max_times>l/2)
			return max_num;
		else
			return 0;
		
    }

	 bool tail_is_1(int n){
        if(floor(float(n/10.0))*10+1==n) return true;
        else return false;
    }
    
    int NumberOf1Between1AndN_Solution(int n)
    {
        int sum=0;
        //if(n==1)return 1;
        for(int i=1;i<=n;i++)
            {
            int j=i;
            while(j)
            {
                if(tail_is_1(j))
                    sum++;
                j/=10;
            }
        }
        return sum;
    }

	 bool not_ugly(int n){
        if(n==1)return false;
        while(n!=1){
			if(n==2||n==3||n==5)return false;
            if(n%2==0){
                n/=2;
            }
            else if(n%3==0){
                n/=3;
            }
            else if(n%5==0){
                n/=5;
            }
			else return true;
			
			if(n==1)return true;
        }
        
        return false;
        
    }
    int GetUglyNumber_Solution(int index) {
    	int num=0;
		int curr_index=0;
        while(curr_index<index){
			num++;
            if(!not_ugly(num))
                curr_index++;
			 
        }
        return num;
    }

	int GetUglyNumber_Solution1(int index) {
        if (index < 7)return index;
        vector<int> res(index);
        res[0] = 1;
        int t2 = 0, t3 = 0, t5 = 0, i;
        for (i = 1; i < index; ++i)
        {
            res[i] = min(res[t2] * 2, min(res[t3] * 3, res[t5] * 5));
            if (res[i] == res[t2] * 2)t2++;
            if (res[i] == res[t3] * 3)t3++;
            if (res[i] == res[t5] * 5)t5++;
        }
        return res[index - 1];
    }

	bool VerifySquenceOfBST1(vector<int> sequence) {
        if(sequence.size()!=0){
            vector<int> left;
            vector<int> right;
            int rootData=sequence[sequence.size()-1];
            int i=0;
            while(rootData>sequence[i]){
                left.push_back(sequence[i]);
                i++;
            }
            for(int j=i;j<sequence.size()-1;j++){
                if(rootData>sequence[j])
                    return false;
                right.push_back(sequence[j]);
            }
            VerifySquenceOfBST1(left);
            VerifySquenceOfBST1(right);
            return true;
        }
        
        return false;

    }

	bool VerifySquenceOfBST(vector<int> sequence) {
		int m=sequence.size();
		vector<int> vec1;
		vector<int> vec2;
		if (m==1) return true;
		if (m==0) return false;
		for(int i=0;i<m;i++)
		{
			if(sequence[i]<sequence[m-1] && vec2.size()==0)
				vec1.push_back(sequence[i]);
			else if(sequence[i]>sequence[m-1])
				vec2.push_back(sequence[i]);
		}
		if(vec1.size()==m-1)
			return (VerifySquenceOfBST(vec1));
		else if(vec2.size()==m-1)
			return (VerifySquenceOfBST(vec2));
		else if(vec1.size()+vec2.size()==m-1)
			return (VerifySquenceOfBST(vec1) && VerifySquenceOfBST(vec2));
		else
			return false;
	}


};
int run(TreeNode *root) {
    if(root->left==NULL || root->right==NULL)
    {
        return 1;
    }
    else
    {
		int temp1=run(root->left);
		int temp2=run(root->right);
		if(temp1<temp2)
			return temp1+1;
		else
			return temp2+1;
        //return (run(root->left))<(run(root->right))?(run(root->left)):(run(root->right)) + 1;
    }
}

int number_mult(int num)
{
	int total=0;
	while(num>=10)
	{
		total++;
		int res=1;
		while(num>0)
		{
			res*=(num-num/10*10);
			num/=10;
		}
		num=res;
	}
	return total;
}

bool is_prime(int a)
{
	for(int i=2;i<=sqrt(a*1.0);i++)
	{
		if(a%i==0) return false;
	}
	return true;
}

bool part_is_prime(int a)
{
	vector<int> temp;
	while(a>0)
	{
		temp.push_back(a-a/10*10);
		a/=10;
	}
	for(int i=0;i<temp.size();i++)
	{
		for(int j=0;j<temp.size()&&j!=i;j++)
		{
			int temp1=temp[i]*10+temp[j];
			if(temp1>10&&is_prime(temp1)) return true;
			temp1=temp[j]*10+temp[i];
			if(temp1>10&&is_prime(temp1)) return true;
		}
	}
	return false;
}


int total_prime(int a,int b)
{
	int total=0;
	for(int i=a;i<=b;i++)
	{
		if(part_is_prime(i))
			total++;
	}
	return total;

}
int min_dif_chara(string s1,string s2)
{
	int len1=s1.size();
	int len2=s2.size();
	string temp;
	if(s1.size()>s2.size())
	{
		len1=s2.size();
		len2=s1.size();
		temp=s1;
		s1=s2;
		s2=temp;
	}

	int max_same=0;
	for(int i=0;i<=len2-len1;i++)
	{
		int once_same=0;
		for(int j=0;j<len1;j++)
		{
			if(s1[j]==s2[i+j])
				once_same++;
		}
		if(once_same>max_same)
			max_same=once_same;
	}
	return len2-(max_same+(len2-len1));
}


bool is_mult_2(int a,int b)
{
	if(a==b) return true;
	if(a<b)
	{
		int temp=a;
		a=b;
		b=temp;
	}
	while(a>=b)
	{
		if(a==b) return true;
		a/=2;
	}
	return false;
}
bool mult2_same(vector<int>arr,int n)
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(!is_mult_2(arr[i],arr[j])) return false;
		}
	}
	return true;
}


int min_segment(vector<int> arr)
{
	int jizhi=0;
	int j=arr.size();
	for(int i=1;i<arr.size()-1;i++)
	{
		if(((arr[i-1]<arr[i] && arr[i+1]<arr[i]) || (arr[i-1]>arr[i] && arr[i+1]>arr[i])) && i!=j+1)
		{
			jizhi++;
			j=i;
		}
		else if(arr[i]==arr[i+1])
		{
			arr[i]=arr[i-1];
			j=i;
		}
	}
	return jizhi+1;
}

long max_power(int* pow,int* pot,int n)
{
	long add=0;
	long max=0;
	long* sum=new long [n];
	long* sub=new long [n];
	for(int i=0;i<n;i++)  
    {  
        long a=pow[i];  
        long b=pot[i];  
        sum[i]=a+b;  
        sub[i]=0;  
        if(b>a)  
        {  
            sub[i]=b-a;   
            add=add+sub[i];  
        }  
  
    }  
          
    for(int i=0;i<n;i++)  
    {  
        if(add+sum[i]-sub[i]>max)  
        {  
            max=add+sum[i]-sub[i];  
        }  
              
    }  
	return max;
}
int depth_tree(TreeNode* node){
    if(node){
		int ldepth=depth_tree(node->left);
		int rdepth=depth_tree(node->right);
        return (max(ldepth,rdepth)+1);
    }
    else{
        return 0;
    }
}
bool IsBalanced_Solution(TreeNode* pRoot) {
	if(abs(depth_tree(pRoot->left)-depth_tree(pRoot->right))>1)
        return false;
    else
        return true;
}
    
void FindNumsAppearOnce(vector<int> data,int* num1,int *num2) {
		
        while(data.size()>0){
            int tmp=data[0];
            data.erase(data.begin());
            vector<int>::iterator index=find(data.begin(),data.end(),tmp);
            int dis=distance(data.begin(),index);
            if(dis>=data.size() || dis<0){
                *num1=*num2;
                *num2=tmp;
            }
			else{
				data.erase(index);
			}
        }
    }
vector<int> FindNumbersWithSum(vector<int> array,int sum) {
        int res=sum*sum;
        vector<int> res1;
        while(array.size()>0){
	    	int tmp=array[0];
            array.erase(array.begin());
            vector<int>::iterator index=find(array.begin(),array.end(),sum-tmp);
            int dis=distance(array.begin(),index);
            if(dis<array.size()&&dis>=0)
                {
                if(res>tmp*array[dis]){
                    res=tmp*array[dis];
                    array.erase(index);
					res1.clear();
					res1.push_back(tmp);
					res1.push_back(array[dis]);
                }
            }
        }
        return res1;
    }

vector<vector<int> > FindContinuousSequence(int sum) {
        vector<vector<int>> res;
        for(int m=2;m<=sum/2;m++){
            vector<int> seq;

				if((sum/m)%2==1&&sum/m/2>=m)
				{
					for(int i=sum/m/2-m+1;i<=sum/m/2+m;i++)
						seq.push_back(i);
					res.push_back(seq);
				}
				if(m%2==1&&sum/m-(m/2)>=1)
				{
					for(int i=sum/m-m/2;i<=sum/m+m/2;i++)
						seq.push_back(i);
					res.push_back(seq);
				}
            
        }
        return res;
    }
bool match(char* str, char* pattern)
{
    if(str[0]=='\0'&&pattern[0]=='\0') return true;
    if((str[0]=='\0'&&pattern[0]!='\0')||(str[0]!='\0'&&pattern[0]=='\0')){
        if(str[0]=='\0'&&pattern[1]=='*') return match(str,pattern+2);
        else return match(str+2,pattern);
    }
    else if((str[0]==pattern[0]||str[0]=='.'||pattern[0]=='.')||(str[0]!=pattern[0] && str[1]=='*'&&pattern[1]=='*')) return match(str+1,pattern+1);
    else if(str[0]!=pattern[0] && str[1]!='*'&&pattern[1]!='*')return false;
    else if(str[0]!=pattern[0] && str[1]=='*') return match(str+1,pattern);
    else return true;
}

ListNode* deleteDuplication(ListNode* head)
{
    if (!head || !head->next) return head;
    ListNode* dummy = new ListNode(-1);dummy->next = head;
    ListNode*pre = dummy, *p1 = head;
    bool flag = 0;
    while (p1&&p1->next) {
        while (p1->next&&p1->val == p1->next->val) {
            p1->next = p1->next->next;
            flag = 1;
        }
        if (flag == 1) { pre->next = p1->next;flag = 0;p1 = p1->next; }
        else {
            p1 = p1->next;
            pre = pre->next;
        }
    }
    return dummy->next;
}
int main()
{
	/*TreeNode * tree=new TreeNode(62);
	tree->left=new TreeNode(47);
	tree->right=new TreeNode(88);
	tree->left->left=new TreeNode(35);
	tree->left->left->left=NULL;
	tree->left->left->right=new TreeNode(37);
	tree->left->right=new TreeNode(51);
	tree->left->right->left=NULL;
	tree->left->right->right=new TreeNode(58);

	tree->right->left=new TreeNode(73);
	tree->right->left->left=NULL;
	tree->right->left->right=NULL;
	tree->right->right=new TreeNode(99);
	tree->right->right->left=new TreeNode(93);
	tree->right->right->right=NULL;
	*/
	//cout<<run(tree)<<endl;
	/*
	solution s;
	int pre[]={4,2,1,3,6,5,7};
	int vin[]={1,2,3,4,5,6,7};
	int back[]={7,4,2,5,8,6,3,1};
	TreeNode *root1=s.reConstructBinaryTree1(pre,0,6,vin,0,6);
	TreeNode *root2=s.reConstructBinaryTree2(back,0,7,vin,0,7);*/
	/*char a[]="hello world haha!";
	s.replaceSpace(a,18);
	s.Mirror(root1);

	int m=4;
	int n=4;
	vector<vector<int>> arr(m);
	//vector<vector<int> > array(m); //这个m一定不能少
//初始化一个m*n的二维数组
	for(int i=0;i<m;i++) {
		arr[i].resize(n);
	}
	for(size_t i=0;i<arr.size();i++)
	{
		for(size_t j=0;j<arr[0].size();j++)
		{
			arr[i][j]=i*arr.size()+j+1;
		}
	}
	//vector<int> res=s.printMatrix(arr);

	int a1[]={1,2,3,4,5};
	int b1[]={4,3,5,1,2};
	vector<int> ain(a1,a1+5);
	vector<int> bin(b1,b1+5);
	bool flag=s.IsPopOrder(ain,bin);
	*/
	//int a1[]={5,7,6,9,11,10,8};
	//int b1[]={1,3,8,5,6,7,4};
	//RandomListNode*head=new RandomListNode(1);
	//head->next=new RandomListNode(2);
	//head->next->next=new RandomListNode(3);
	//head->next->random=head;
	//head->next->next->random=head->next;
	//vector<int> ain(a1,a1+7);
	//vector<int> bin(b1,b1+7);
	//bool result=s.VerifySquenceOfBST1(bin);
	//result=s.VerifySquenceOfBST(bin);
	//vector<int> res=s.PrintFromTopToBottom(root1);
	//vector<vector<int>> vec=s.FindPath(root1,14);
	//RandomListNode*res=s.Clone(head);
	/*ListNode *list1=new ListNode(1);
	list1->next=new ListNode(2);
	list1->next->next=new ListNode(3);
	ListNode*res=s.FindKthToTail(list1,1);
	TreeNode*res_list=s.Convert(root1);
	*/
	//int res=s.MoreThanHalfNum_Solution(bin);
	//string str="aabc";
	//vector<string> result=s.Permutation(str);
	//int max_val=100;
	//cout<<s.GetUglyNumber_Solution(max_val)<<endl;
	//cout<<s.GetUglyNumber_Solution1(max_val)<<endl;
	//cout<<number_mult(258)<<endl;
	//cout<<total_prime(37,98)<<endl;
	//string s1,s2;
	//cin>>s1;
	//cin>>s2;
	//cout<<min_dif_chara(s1,s2);
	//int n;
	//cin>>n;
	//vector<int> arr;
	//int num;
	//ifstream fin;
	/*fin.open("F:\\C++test\\lesson\\test\\offer\\data1.txt");
	while(fin>>num){
		arr.push_back(num);
	}
	*/
	/*for(int i=0;i<n;i++)
	{
		cin>>num;
		arr.push_back(num);
	}*/
	//if(mult2_same(arr,n))
	//	cout<<"YES";
	//else
	//	cout<<"NO";
	//cout<<min_segment(arr);
	//int n;
	//cin>>n;
	//int pow[100000];
	//int pot[100000];
	//for(int i=0;i<n;i++)
	//{
	//	cin>>pow[i];
	//	cin>>pot[i];
	//}
	//cout<<max_power(pow,pot,n)<<endl;
	//bool res=IsBalanced_Solution(tree);
	/*int a1[]={2,3,1,2,3,3,2,6};
	vector<int> ain(a1,a1+8);
	vector<vector<int> >res;//返回对应值的索引
	vector<int>data(1,0);//存放临时索引
	vector<int>index;//返回对应的值
	vector<int> tmp(100,-1);//临时存放标志位
	for(int i=0;i<ain.size();i++)
	{
		if(tmp[ain[i]]<0)
		{
			data[0]=i;
			tmp[ain[i]]=res.size();
			index.push_back(ain[i]);
			res.push_back(data);
		}
		else
		{
			res[tmp[ain[i]]].push_back(i);
		}
	}
	ofstream fout;
	fout.open("F:\\C++test\\lesson\\test\\offer\\data1.txt");
	for(int i=0;i<res.size();i++)
	{
		for(int j=0;j<res[i].size();j++)
			fout<<res[i][j]<<" ";
		fout<<-1<<endl;
	}
	fout.close();
	ifstream fin;
	vector<int>in_line;
	vector<vector<int> >in_total;
	fin.open("F:\\C++test\\lesson\\test\\offer\\data1.txt");
	int num;
	while(fin>>num)
	{
		if(num==-1){
			in_total.push_back(in_line);
			in_line.clear();
		}
		else
			in_line.push_back(num);
	}
	fin.close();
	//int a,b;
	//vector<int> res=FindNumbersWithSum(ain,15);
	//vector<vector<int> >res= FindContinuousSequence(99);
	int a=5,b=4;
	double s;
	s=pow(double(a),2)/4;
	*/
	//char a[]={'\0'};
	//char b[]={'.','*','\0'};
	//bool res=match(a,b);
	ListNode *list1=new ListNode(1);
	ListNode *head=list1;
	int num;
	while(cin>>num){
		list1->next=new ListNode(num);
		list1=list1->next;
	}
	list1->next=NULL;
	ListNode*res=deleteDuplication(head->next);
	return 0;
}