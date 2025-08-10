# Documentation de la classe `UITextComponent`

## 1. Rôle et Objectif

La classe `UITextComponent` est une classe de base **abstraite** qui sert de fondation pour tous les composants d'interface utilisateur qui ont besoin d'afficher ou de gérer du texte. Son objectif principal est la **factorisation de code** : elle regroupe la logique commune de stockage et de manipulation d'une chaîne de caractères (`String`) pour éviter la duplication dans les classes dérivées.

Des composants comme `UILabel`, `UIButton`, `UISlider`, et `UISwitch` héritent de `UITextComponent` pour obtenir la fonctionnalité de "label" ou de "texte".

## 2. Conception et Héritage

`UITextComponent` s'inscrit dans la hiérarchie des classes de l'interface utilisateur comme suit :
`UIComponent` -> **`UITextComponent`** -> `UILabel`, `UIButton`, etc.

Elle hérite de `UIComponent`, ce qui lui donne les propriétés de base de tout élément d'interface (position, taille, état activé/désactivé). Elle ajoute à cela un membre `protected String _text`.

**Important** : Cette classe n'est pas destinée à être instanciée directement. Elle sert uniquement de parent pour des classes plus concrètes.

## 3. Fonctionnement Détaillé

### a. Constructeur
```cpp
UITextComponent(int x, int y, int w, int h, const String& text);
```
Le constructeur initialise les propriétés géométriques en appelant le constructeur de sa classe parente (`UIComponent`) et initialise la variable membre `_text` avec le texte fourni.

### b. `setText(const String& newText)`
Cette méthode virtuelle permet de modifier le texte du composant après sa création. Elle inclut une optimisation importante :

```cpp
void UITextComponent::setText(const String& newText) {
    if (_text != newText) {
        _text = newText;
        // Une classe dérivée devrait ici déclencher un redessin.
        // setNeedsRedraw(); 
    }
}
```
La mise à jour de la variable `_text` n'est effectuée que si le nouveau texte est différent de l'ancien. Cela évite des opérations de redessin inutiles si le texte n'a pas changé. Les classes filles sont responsables de déclencher le redessin après avoir appelé cette méthode de base.

### c. `getText() const`
Cette méthode retourne une référence constante vers le texte actuel du composant. L'utilisation d'une référence est efficace car elle évite de copier la chaîne de caractères. Le `const` garantit que le texte ne peut pas être modifié via cette méthode.

## 4. Utilisation et Exemples

Un développeur n'utilise généralement pas `UITextComponent` directement, mais plutôt ses classes filles.

### Exemple : Implémentation d'un `UILabel`
Voici comment une classe `UILabel` pourrait hériter de `UITextComponent` et utiliser ses fonctionnalités.

```cpp
// Fichier : UILabel.h (conceptuel)
#include "UITextComponent.h"

class UILabel : public UITextComponent {
public:
    UILabel(int x, int y, int w, int h, const String& text);
    
    // Redéfinition de setText pour ajouter le redessin
    void setText(const String& newText) override;

    void draw(TFT_eSPI& tft) override;
};

// Fichier : UILabel.cpp (conceptuel)
#include "UILabel.h"

UILabel::UILabel(int x, int y, int w, int h, const String& text)
    : UITextComponent(x, y, w, h, text) {}

void UILabel::setText(const String& newText) {
    // Appelle la méthode de la classe de base pour la logique de mise à jour
    UITextComponent::setText(newText);
    // Déclenche un redessin pour que le changement soit visible
    setNeedsRedraw();
}

void UILabel::draw(TFT_eSPI& tft) {
    // Utilise la variable _text (via getText()) héritée de UITextComponent
    tft.drawString(getText(), _x, _y); 
}
```
Dans cet exemple, `UILabel` bénéficie de la gestion du texte fournie par `UITextComponent` et se concentre uniquement sur sa propre logique : le dessin.

## 5. API de Référence (Fichier d'en-tête `UITextComponent.h`)

```cpp
#ifndef UITEXTCOMPONENT_H
#define UITEXTCOMPONENT_H

#include "UIComponent.h"
#include <Arduino.h> // Pour la classe String

class UITextComponent : public UIComponent {
public:
    UITextComponent(int x, int y, int w, int h, const String& text);
    virtual ~UITextComponent() = default;

    virtual void setText(const String& newText);
    virtual const String& getText() const;

protected:
    String _text; ///< Le texte du composant.
};

#endif // UITEXTCOMPONENT_H
```