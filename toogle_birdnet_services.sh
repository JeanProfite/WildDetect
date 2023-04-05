#!/bin/bash

# Liste des services à modifier
services=(
    birdnet_analysis.service
    birdnet_log.service
    birdnet_recording.service
    birdnet_server.service
    birdnet_stats.service
    chart_viewer.service
    extraction.service
    livestream.service
    spectrogram_viewer.service
    web_terminal.service
)

# Demander confirmation à l'utilisateur
read -p "Êtes-vous sûr de vouloir activer/désactiver ces services ? (y/n) " confirm

# Si l'utilisateur confirme, continuer
if [[ $confirm =~ ^[yY]$ ]]; then

    # Parcourir la liste des services
    for service in "${services[@]}"; do

        # Vérifier l'état actuel du service
        is_enabled=$(systemctl is-enabled $service)

        # Si le service est activé, le désactiver et le stopper
        if [[ $is_enabled == "enabled" ]]; then
            systemctl stop $service
            systemctl disable $service
            echo "Service $service désactivé et arrêté"
        # Si le service est désactivé, l'activer et le démarrer
        else
            systemctl enable $service
            systemctl start $service
            echo "Service $service activé et démarré"
        fi

    done

else
    echo "Opération annulée"
fi

