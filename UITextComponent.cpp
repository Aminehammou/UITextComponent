#include "UITextComponent.h"

/**
 * @brief Constructeur de UITextComponent.
 *
 * Initialise le composant avec sa position, ses dimensions et son texte.
 * Il appelle le constructeur de la classe de base UIComponent.
 *
 * @param u8f Référence à l'objet U8g2_for_TFT_eSPI pour le rendu des polices.
 * @param rect Le rectangle définissant la position et les dimensions du composant.
 * @param text Le texte initial du composant.
 */
UITextComponent::UITextComponent(U8g2_for_TFT_eSPI& u8f, const UIRect& rect, const String& text) 
    : UIComponent(rect), _u8f(u8f), _text(text) {}

/**
 * @brief Modifie le texte du composant.
 *
 * Si le nouveau texte est différent de l'ancien, il est mis à jour.
 * Cela évite des opérations inutiles si le texte n'a pas changé.
 *
 * @param newText Le nouveau texte à afficher.
 */
void UITextComponent::setText(const String& newText) {
    if (_text != newText) {
        _text = newText;
        setDirty(true); // Marquer le composant comme nécessitant un redessin
    }
}

/**
 * @brief Récupère le texte actuel du composant.
 *
 * @return const String& Une référence constante vers le texte.
 */
const String& UITextComponent::getText() const {
    return _text;
}