void BFS(int v ,int n)
{
    q.push(v);
    visit[v] = true;
    while( ! q.empty() )
    {
        int front = q.front();
        printf("%d ",front);
        for( int i = 0 ;i < n ;++i )
        {
            if( graph[front][i] == 1 && visit[i] == false )
            {
               visit[i] = true;
                q.push(i);
            }
        }
        q.pop();
    }
}
void init_visit(int n)
{
    for(int i = 0 ; i < n ;++i )
    {
        visit[i] = false;
    }
}
int main()
{
    int n;
    cout<<"���붥������"<<endl;
    cin>>n;
    cout<<"����ͼ���ڽӾ���"<<endl;
    int f;
    for( int i = 0 ;i< n ;++i )
    {
        for(int j = 0 ; j < n ;++j)
        {
            cin>>f;
            graph[i][j] = f;
        }
    }
    init_visit(n);
    cout<<"BFS����Ϊ��"<<endl;
    for( int i = 0 ; i < n ; ++i)
    {
        if(visit[i]==false)
        {
            BFS(i,n);
        }
    }
    cout<<endl;
    return 0;

}
