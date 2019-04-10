#pragma once
// Generated using ReClass 2016

class cEntity;
class cJogador;
class cRecurso;
class Vector2;

class Vector2 {
public:
	float x;
	float y;
};
class cEntity
{
public:
	char pad_0x0000[0x34]; //0x0000
	float Saude; //0x0034 
	char pad_0x0005[0x4];
	Vector2 Posicao; //0x0038 
	char pad_0x0040[0x8]; //0x0040
	byte Time; //0x0048 
	char pad_0x0049[0x37]; //0x0049
	byte EmMovimento; //0x0080 

}; //Size=0x04F0
std::vector<DWORD> ListaInimigos;

class cGameController
{
public:
	char pad_0x0000[0x3C]; //0x0000
	cRecurso* pRecursos; //0x003C 
	char pad_0x0040[0xD0]; //0x0040
	Vector2 CameraPos; //0x0110 

}; //Size=0x04C0

class cRecurso
{
public:
	float Comida; //0x0000 
	float Madeira; //0x0004 
	float Pedra; //0x0008 
	float Ouro; //0x000C 
}; //Size=0x0084

#define addrFuncaoEntityLoop 0xA5ABE
#define offFuncaoEntityTamanho 6
#define addrFuncaoJogador 0x464094
#define offFuncaoJogadorTamanho 15
#define pEntSelecionado 0x6B8AA0

DWORD JBase = 0x0;
DWORD FuncEntity = 0x0;
DWORD FuncEntityFinal = 0x0;
DWORD FuncController = 0x0;
DWORD FuncControllerFinal = 0x0;
DWORD dController = 0x0;

cEntity PegarEntity(DWORD dEnt) {
	return *(cEntity*)dEnt;

}

bool CheckDWORD(DWORD d) {
	if ((d > 0 && d < 0xFFFFFFFF))
		return true;
	else
		return false;
}
void AdicionarEntity(DWORD ent) {

	for (int i = 0; i < ListaInimigos.size(); i++) {
		if (ent == ListaInimigos.at(i))
			return;
	}

	ListaInimigos.push_back(ent);

}


/**/