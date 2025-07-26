#ifndef VOL_H
#define VOL_H
#include <string>
#include <memory>

/**
 * \class Vol
 * \brief Classe abstraite représentant un vol d'aéroport.
 *
 *        La classe contient les informations générales d’un vol, soit :
 *        le numéro de vol, le nom de la compagnie aérienne, l’heure prévue, et la ville
 *        (de destination pour un départ ou de provenance pour une arrivée).
 *
 *        Cette classe est abstraite et doit être dérivée pour des cas spécifiques.
 *        Elle valide l’état interne à l’aide d’un invariant, et permet de formater et cloner le vol.
 *
 * \invariant La validité peut être vérifiée avec les fonctions suivante :
 * bool estNumeroVolValide(m_numero),bool estNomValide(m_compagnie),bool estFormat24HValide(m_heure),bool estNomValide(m_ville).
 */
namespace aerien {
    class Vol {
    public:
        Vol(const std::string &p_numero, const std::string &p_compagnie, const std::string &p_heure,
            const std::string &p_ville);


        const std::string &reqNumero() const;

        const std::string &reqCompagnie() const;

        const std::string &reqHeure() const;

        const std::string &reqVille() const;

        void asgHeureVol(const std::string &p_heure);
        void asgNumero(const std::string &p_numero);
        void asgCompagnie(const std::string &p_compagnie);
        void asgVille(const std::string &p_ville);

        Vol&operator=(const Vol& p_vol);

        virtual ~Vol()=default;

        bool operator==(const Vol &p_vol) const;

        virtual std::unique_ptr<Vol> clone() const = 0;
        virtual bool estDepart() const =0;

        virtual std::string reqVolFormate() const;


    private:
        std::string m_numero;
        std::string m_compagnie;
        std::string m_heure;
        std::string m_ville;

        void verifierInvariant() const;
    };
}
#endif /* VOL_H */

