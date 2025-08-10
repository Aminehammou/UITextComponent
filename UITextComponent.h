#ifndef UITEXTCOMPONENT_H
#define UITEXTCOMPONENT_H

#include "U8g2_for_TFT_eSPI.h"
#include "UIRect.h"
#include <UIComponent.h>
#include <Arduino.h> // Pour la classe String

/**
 * @class UITextComponent
 * @brief Classe de base pour les composants de l'interface utilisateur contenant du texte.
 * 
 * Cette classe factorise la gestion du texte (label) pour des composants
 * comme UILabel et UIButton. Elle hérite de UIComponent et ajoute la
 * capacité de stocker et de manipuler une chaîne de caractères.
 */
class UITextComponent : public UIComponent {
public:
    UITextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text);
    virtual ~UITextComponent() = default;

    // Méthodes communes pour la manipulation du texte
    virtual void setText(const String& newText);
    virtual const String& getText() const;
protected:
    U8g2_for_TFT_eSPI& _u8f; ///< Référence à l'objet U8g2 pour le rendu des polices.
    String _text; ///< Le texte du composant.
};

#endif // UITEXTCOMPONENT_H