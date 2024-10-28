# Exigences du Système de Signalisation Ferroviaire

## 1. Exigences Système (SYS)

### SYS_REQ_001 [SIL4]
Le système DOIT gérer trois aspects de signalisation : Rouge, Vert et Jaune.

### SYS_REQ_002 [SIL4]
Le système DOIT maintenir un état cohérent en toutes circonstances.

### SYS_REQ_003 [SIL4]
Le système DOIT enregistrer tous les changements d'état avec horodatage.

### SYS_REQ_004 [SIL4]
Le temps de réponse pour un changement d'état NE DOIT PAS excéder 100ms.

## 2. Exigences de Sécurité (SAF)

### SAF_REQ_001 [SIL4]
Le système DOIT defaulter à l'aspect Rouge en cas de défaillance.

### SAF_REQ_002 [SIL4]
Toute transition d'état DOIT être validée avant exécution.

### SAF_REQ_003 [SIL4]
Le système DOIT empêcher les transitions d'état interdites.

### SAF_REQ_004 [SIL4]
L'état du système DOIT être persisté de manière redondante.

## 3. Exigences Fonctionnelles (FUNC)

### FUNC_REQ_001 [SIL4]
Le système DOIT supporter l'annulation des commandes (undo).

### FUNC_REQ_002 [SIL4]
Le système DOIT supporter la réexécution des commandes (redo).

### FUNC_REQ_003 [SIL4]
Le système DOIT notifier les changements d'état aux systèmes externes.

### FUNC_REQ_004 [SIL3]
Le système DOIT fournir une interface pour la supervision en temps réel.

## 4. Exigences de Performance (PERF)

### PERF_REQ_001 [SIL3]
Le système DOIT traiter au moins 100 commandes par seconde.

### PERF_REQ_002 [SIL3]
La latence de notification NE DOIT PAS excéder 50ms.

## 5. Exigences de Maintenance (MAINT)

### MAINT_REQ_001 [SIL2]
Le système DOIT journaliser toutes les opérations de maintenance.

### MAINT_REQ_002 [SIL3]
Le système DOIT supporter la mise à jour à chaud des paramètres.

## 6. Exigences de Démonstration (DEMO)

### DEMO_REQ_001 [SIL4]
Le programme de démonstration DOIT illustrer les transitions d'états valides dans une séquence prédéfinie.

### DEMO_REQ_002 [SIL4]
Le programme de démonstration DOIT démontrer la capacité d'annulation et de réexécution des commandes.

### DEMO_REQ_003 [SIL4]
Le programme de démonstration DOIT assurer un retour à l'état sûr (Rouge) en fin d'exécution.

### DEMO_REQ_004 [SIL4]
Le programme de démonstration DOIT gérer et afficher clairement les erreurs potentielles.

### DEMO_REQ_005 [SIL4]
Le programme de démonstration DOIT illustrer le mécanisme de notification des changements d'état.

## 7. Matrices de Traçabilité

### 7.1 Matrice Source → Test

| Exigence      | Test ID       | Description du Test |
|---------------|---------------|------------------|
| SYS_REQ_001   | TEST_001     | Vérification des trois aspects |
| DEMO_REQ_001  | TEST_002     | Séquence de transitions |
| DEMO_REQ_002  | TEST_003     | Undo/Redo des commandes |
| DEMO_REQ_003  | TEST_004     | Retour à l'état sûr |

### 7.2 Matrice Code → Exigence

| Classe/Méthode | Exigence    | Niveau SIL |
|----------------|-------------|------------|
| SignalDemo     | DEMO_REQ_001| SIL4       |
| main           | DEMO_REQ_003| SIL4       |
| aspectChanged  | DEMO_REQ_005| SIL4       |

## 8. Règles de Validation

### 8.1 Transitions d'État Autorisées
- Rouge → Jaune
- Jaune → Vert
- Vert → Jaune
- Jaune → Rouge

### 8.2 Conditions de Transition
1. La transition vers Vert nécessite :
   - État précédent : Jaune
   - Voie libre confirmée
   - Aucune alarme active

2. La transition vers Rouge est autorisée depuis n'importe quel état

## 9. Références Normatives
- CENELEC 50128:2011
- CENELEC 50126-1:2017
- CENELEC 50129:2018
