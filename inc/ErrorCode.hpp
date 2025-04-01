/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPL_Error.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lboiteux <lboiteux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 22:25:35 by lboiteux          #+#    #+#             */
/*   Updated: 2025/03/31 22:35:52 by lboiteux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define RPL_UMODEIS            221  // <modes utilisateurs>
#define RPL_WHOISUSER          311  // <nick> <nom> <domaine> <vrai nom>
#define RPL_WHOISSERVER        312  // <nick> <serveur> [<infos serveur>]
#define RPL_WHOISOPERATOR      313  // <nick>
#define RPL_WHOWASUSER         314  // <nick> <nom> <domaine> <vrai nom>
#define RPL_WHOISIDLE          317  // <nick> <temps d'idle en secondes>
#define RPL_ENDOFWHOIS         318  // <nick>
#define RPL_WHOISCHANNELS      319  // <nick> <liste de channels avec status>
#define RPL_LIST               322  // <nom du chan> <nombre d'utilisateurs préssents> <topic>
#define RPL_LISTEND            323  // <>
#define RPL_CHANNELMODEIS      324  // <modes chan>
#define RPL_NOTOPIC            331  // <chan>
#define RPL_TOPIC              332  // <chan> <topic>
#define RPL_INVITING           341  // <chan> <nick>
#define RPL_NAMREPLY           353  // <chan> <liste des utilisateurs avec status>
#define RPL_ENDOFNAMES         366  // <chan>
#define RPL_BANLIST            367  // <chan> <masque d'utilisateur banni>
#define RPL_ENDOFBANLIST       368  // <chan>
#define RPL_ENDOFWHOWAS        369  // <nick>
#define RPL_YOUREOPER          381  // <>

#define ERR_NOSUCHNICK         401  // <nick>
#define ERR_NOSUCHSERVER       404  // <serveur>
#define ERR_NOSUCHCHANNEL      403  // <chan>
#define ERR_CANNOTSENDTOCHAN   404  // <chan>
#define ERR_WASNOSUCHNICK      406  // <nick>
#define ERR_NOORIGIN           409  // <>
#define ERR_NORECIPIENT        411  // <>
#define ERR_NOTEXTTOSEND       412  // <>
#define ERR_NOTOPLEVEL         413  // <masque d'utilisateur>
#define ERR_WILDTOPLEVEL       414  // <masque>
#define ERR_NONICKNAMEGIVEN    431  // <nick>
#define ERR_ERRONEUSNICKNAME   432  // <nick>
#define ERR_NICKNAMEINUSE      433  // <nick>
#define ERR_NICKCOLLISION      436  // <nick>
#define ERR_NOTONCHANNEL       442  // <chan>
#define ERR_USERONCHANNEL      443  // <nick>
#define ERR_NEEDMOREPARAMS     461  // <commande>
#define ERR_ALREADYREGISTRED   462  // <>
#define ERR_PASSWDMISMATCH     464  // <>
#define ERR_KEYSET             467  // <chan>
#define ERR_CHANNELISFULL      471  // <chan>
#define ERR_UNKNOWNMODE        472  // <caractère>
#define ERR_INVITEONLYCHAN     473  // <chan>
#define ERR_BANNEDFROMCHAN     474  // <chan>
#define ERR_BADCHANNELKEY      475  // <chan>
#define ERR_NOPRIVILEGES       481  // <>
#define ERR_CHANOPRIVSNEEDED   482  // <chan>
#define ERR_CANNTKILLSERVER    483  // <>
#define ERR_NOOPERHOST         491  // <>
#define ERR_UMODUUNKNOWNFLAG   501  // <>
#define ERR_USERSDONTMATCH     502  // <>