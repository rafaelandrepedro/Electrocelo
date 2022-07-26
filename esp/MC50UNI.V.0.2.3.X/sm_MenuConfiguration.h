/* 
 * File:   sm_MenuConfiguration.h
 * Author: cpereira
 *
 * Created on 15 de Setembro de 2014, 14:18
 */

#ifndef SM_MENUCONFIGURATION_H
#define	SM_MENUCONFIGURATION_H


#ifdef	__cplusplus
extern "C" {
#endif

typedef enum {
	st_MainMenu,			/**< Estado onde corre o MenuPrincipal. */
	st_EditParameter,		/**< Estado onde se efectuda a edição dos parametros. */
	st_SaveParameter,		/**<Estado  se sinaliza que a edição foi efectuada com sucesso. */
    st_Counter,             /**<Estado que mostra o numero de manobras. */
    st_SelectRemote,        /**<Estado para seleccionar o Comando onde guardar a posição. */
    st_SaveRemotes,         /**<Estado que guarda a posição. */
    st_LearningMode,
}sm_state_Menu_t;

typedef enum {
	Automatic,
    Manual
}ProgramingType;

typedef enum {
    Up,
    Down
}changeParameter_en;

typedef enum {
    P_Menu,     // PX menu
    E_Menu,     // EX menu
    Direction_Menu,
    TypeMotor_Menu,    
    P0_SMenu,
    P1_SMenu,   // P1 submenu
    P2_SMenu,   // P2 submenu
    P4_SMenu,   // P4 submenu
    P5_SMenu,   // P5 submenu
    P6_SMenu,   // P6 submenu
    E0_SMenu,   // E0 submenu
    E1_SMenu,        
     // Sub menu do tipo motor        
    S_Menu,     // SX menu
    Del_Menu    // Del menu
    
}menuLists_en;

#define NUM_MENU_OPTIONS    (10)

typedef struct {
    display_group_st    menuList[NUM_MENU_OPTIONS];
    menuLists_en        lastMenu;
    menuLists_en        actualMenu;
    char                menuSize;
    char                parameterSelected;
    char                lastMainParameterSelected;
}menu_Struct;

typedef struct 
{
	char            position;
	unsigned char*  Value;
    unsigned char   tempValue;
	char            Max;
	char            Min;
}edit_Parameter_st;

extern sm_t menuConfiguration_stateMachine;

/**
 * \brief	Função que controla o estado e do modem e gere as prioridades do modem.
 *
 * \param psm	Apontador para estrutura da maquina de estados
 *
 * \return void
 */
void sm_execute_menuConfiguration( sm_t *psm );

void load_New_Menu(menuLists_en Menu);

char setValueToEdit(menuLists_en menuType, char ParameterSelected );

void controlSelectRemote(void);

void controlSaveRemote(void);

void controlLearnDigit(void);

#ifdef	__cplusplus
}
#endif

#endif	/* SM_MENUCONFIGURATION_H */

