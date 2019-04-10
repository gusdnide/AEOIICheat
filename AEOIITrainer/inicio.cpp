#include "Includes.h"

#pragma region Hooks D3D


#pragma endregion Hooks do directX para desenhar na tela
#pragma region Minhas Hooks
__declspec(naked) HRESULT WINAPI  hkGetEntities()
{
	static DWORD dEntity = 0x0;
	__asm {
		mov dEntity, ecx
		mov ecx, [ecx + 0xFC]
		PUSHAD
	}

	if (CheckDWORD(dEntity))
		AdicionarEntity(dEntity);

	__asm {
		POPAD
		JMP FuncEntityFinal
	}
}

__declspec(naked) HRESULT WINAPI  hkGetGameController()
{
	static DWORD dTemp = 0x0;
	__asm {
		mov dTemp, edx
		movss xmm0, [edx + 0x00000110]
		PUSHAD
	}
	if (CheckDWORD(dTemp))
		dController = dTemp;
	__asm {
		POPAD
		JMP FuncControllerFinal
	}
}
#pragma endregion Hooks para buscar ponteiros no jogo.
#pragma region Rotinas
BOOL Rotina() {

	system("color 0A");
	JBase = (DWORD)GetModuleHandle("AoK HD.exe");



	printf("Buscando Enderecos...\n");
	printf("[*] JBase: [0x%X]\n", JBase);

	/* Endereços HOOK */
	FuncEntity = JBase + addrFuncaoEntityLoop;
	FuncEntityFinal = FuncEntity + offFuncaoEntityTamanho;
	printf("[*] FuncEntity: [0x%X] Fim: [0x%X]\n", FuncEntity, FuncEntityFinal);

	FuncController = JBase + addrFuncaoJogador;
	FuncControllerFinal = FuncController + offFuncaoJogadorTamanho;
	printf("[*] FuncGameController: [0x%X] Fim: [0x%X]\n", FuncController, FuncControllerFinal);

	Sleep(1500);
	printf("[*] Criando hooks...\n");
	DetourCreate((PBYTE)FuncEntity, (PBYTE)hkGetEntities, offFuncaoEntityTamanho);
	DetourCreate((PBYTE)FuncController, (PBYTE)hkGetGameController, offFuncaoJogadorTamanho);

	while (true) {

		DWORD dEntPointer = *(DWORD*)(JBase + pEntSelecionado);


		if (CheckDWORD(dEntPointer))
		{
			cEntity entFocus = *(cEntity*)dEntPointer;
			/*Console*/
			system("cls");
			if (CheckDWORD(dController)) {
				cGameController Jogador = *(cGameController*)dController;
				printf("[*]Recursos [%F, %F, %F, %F]\n[*]CameraX: [%F]\tCameraY:[%F]\n", Jogador.pRecursos->Comida, Jogador.pRecursos->Madeira, Jogador.pRecursos->Ouro, Jogador.pRecursos->Pedra, Jogador.CameraPos.x, Jogador.CameraPos.y);

				printf("[*]Width: [%d] Heigth: [%d]\n", 800, 600);
			}
			for (int i = 0; i < ListaInimigos.size(); i++) {
				cEntity Inimigo = *(cEntity*)ListaInimigos.at(i);
				printf("[*] Inimigo [%d] PosX: [%F] PosY: [%F] Saude: [%F]\n", i, Inimigo.Posicao.x, Inimigo.Posicao.y, Inimigo.Saude);

			}
		}
		//dController = 0x0;
		ListaInimigos.clear();
		Sleep(300);
	}
	return false;
}

#pragma endregion Rotinas para as threads criada.





BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Rotina, 0, 0, 0);
		//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)RotinaD3D, 0, 0, 0);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:

		break;
	}
	return TRUE;
}

