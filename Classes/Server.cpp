#include<Server.h>
USING_NS_CC;

extern char players[1] = { 0 };
std::vector<socket_ptr> client;
boost::recursive_mutex cs;//��֤�̰߳�ȫ
void Server::CreateAccept_thread()
{
	io_service service;
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
	while (players[0] < 3)
	{
		socket_ptr sock(new ip::tcp::socket(service));
		acceptor.accept(*sock);
		boost::recursive_mutex::scoped_lock lk(cs);//��ֹ����
		players[0]++;
		log("%d", players[0]);
		sock->write_some(buffer(players));//�������ӵ���Ҵ��������Ŀ�����ڲ��ܷ���int���ͣ���char���棩
		client.push_back(sock);
	}

}
void Server::HandleRequest(socket_ptr sock)
{
	boost::recursive_mutex::scoped_lock lk(cs);//��ֹ����

}
void Server::Answer_to_client(socket_ptr sock)
{
	boost::recursive_mutex::scoped_lock lk(cs);//��ֹ����

}
void Server::Loop_thread()
{
	while (1)
	{
		for (auto b = client.begin(), e = client.end(); b != e; b++)
		{
			HandleRequest(*b);
			Answer_to_client(*b);
		}
	}
}