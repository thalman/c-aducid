/* Copyright(c) 2015 ANECT a.s.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __ADUCIDPP_H__
#define __ADUCIDPP_H__

#include <aducid.h>
#include <string>
#include <map>
#include <vector>

/**
 * \defgroup AducidClient ADUCID C++ SDK
 * @{
 */
namespace aducid
{

    using namespace std;
    
    /**
     * \brief AducidClient class for ADUCID authentication
     *
     * AducidClient encapsulates C ADUCID interface. It uses standard C++ classes for
     * lists and cares about dynamic memory allocation/deallocation.
     */
    class AducidClient {
    public:
        /**
         * \brief Creates new AducidClient object
         * \param AIM AIM server address
         * \see aducid_new
         *
         * Constructor creates new AducidClient object. The parameter is
         * address of AIM server. See \see aducid_new for possible formats.
         */
        ADUCID_PUBLIC_FUNC AducidClient(const string &AIM);
        ADUCID_PUBLIC_FUNC AducidClient(const char *AIM);

        /**
         * \brief Get or set authId.
         *@{
         */
        ADUCID_PUBLIC_FUNC string authId() const;
        ADUCID_PUBLIC_FUNC void authId(const string &authId);
        ADUCID_PUBLIC_FUNC void authId(const char *authId);
        /**@}*/
        
        /**
         * \name authKey
         * \brief Get or set authKey.
         *@{
         */
        ADUCID_PUBLIC_FUNC string authKey() const;
        ADUCID_PUBLIC_FUNC void authKey(const string &authKey);
        ADUCID_PUBLIC_FUNC void authKey(const char *authKey);
        /**@}*/
        
        /**
         * \name bindingId
         * \brief Get or set bindingId.
         *@{
         */
        ADUCID_PUBLIC_FUNC string bindingId() const;
        ADUCID_PUBLIC_FUNC void bindingId(const string &bindingId);
        ADUCID_PUBLIC_FUNC void bindingId(const char *bindingId);
        /**@}*/
        
        /**
         * \name bindingKey
         * \brief Get or set bindingKey.
         *@{
         */
        ADUCID_PUBLIC_FUNC string bindingKey() const;
        ADUCID_PUBLIC_FUNC void bindingKey(const string &authKey);
        ADUCID_PUBLIC_FUNC void bindingKey(const char *authKey);
        /**@}*/
        
        /**
         * \name open
         * \brief Starts "open" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_open
         *@{
         */
        ADUCID_PUBLIC_FUNC bool open(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool open(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name init
         * \brief Starts "init" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_init
         *@{
         */
        ADUCID_PUBLIC_FUNC bool init(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool init(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name change
         * \brief Starts "change" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_change
         *@{
         */
        ADUCID_PUBLIC_FUNC bool change(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool change(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name rechange
         * \brief Starts "change" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_change
         *@{
         */
        ADUCID_PUBLIC_FUNC bool rechange(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool rechange(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name reinit
         * \brief Starts "reinit" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_reinit
         *@{
         */
        ADUCID_PUBLIC_FUNC bool reinit(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool reinit(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name deleteIdentity
         * \brief Starts "delete" operation
         * \param peigReturnURL URL for application return address.
         * \see aducid_delete
         *@{
         */
        ADUCID_PUBLIC_FUNC bool deleteIdentity(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool deleteIdentity(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name initPersonalFactor
         * \brief Inititates personal factor
         * \param peigReturnURL URL for application return address.
         * \see aducid_init_personal_factor
         *@{
         */
        ADUCID_PUBLIC_FUNC bool initPersonalFactor(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool initPersonalFactor(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name changePersonalFactor
         * \brief Inititates personal factor change
         * \param peigReturnURL URL for application return address.
         * \see aducid_change_personal_factor
         *@{
         */
        ADUCID_PUBLIC_FUNC bool changePersonalFactor(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool changePersonalFactor(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name deletePersonalFactor
         * \brief Inititates operation for deleting personal factor
         * \param peigReturnURL URL for application return address.
         * \see aducid_delete_personal_factor
         *@{
         */
        ADUCID_PUBLIC_FUNC bool deletePersonalFactor(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool deletePersonalFactor(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name verifyPersonalFactor
         * \brief Inititates operation for personal factor verification.
         * \param peigReturnURL URL for application return address.
         * \see aducid_verify_personal_factor
         *@{
         */
        ADUCID_PUBLIC_FUNC bool verifyPersonalFactor(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool verifyPersonalFactor(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name createRoomByStory
         * \brief Creates room for pairing peigs.
         * \param peigReturnURL URL for application return address.
         * \see aducid_create_room_by_story
         *@{
         */
        ADUCID_PUBLIC_FUNC bool createRoomByStory(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool createRoomByStory(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name enterRoomByStory
         * \brief Enters room for pairing peigs previously created by createRoomByStory.
         * \param peigReturnURL URL for application return address.
         * \see aducid_enter_room_by_story
         * \see createRoomByStory
         *@{
         */
        ADUCID_PUBLIC_FUNC bool enterRoomByStory(const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool enterRoomByStory(const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name createRoomByName
         * \brief Creates room for pairing peigs.
         * \param name room name to be created.
         * \param peigReturnURL URL for application return address.
         * \see aducid_create_room_by_story
         *@{
         */
        ADUCID_PUBLIC_FUNC bool createRoomByName(const char *name, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool createRoomByName(const string &name, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name enterRoomByName
         * \brief Enters room for pairing peigs previously created by createRoomByName.
         * \param name room name to be created.
         * \param peigReturnURL URL for application return address.
         * \see aducid_enter_room_by_name
         * \see createRoomByName
         *@{
         */
        ADUCID_PUBLIC_FUNC bool enterRoomByName(const char *name, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool enterRoomByName(const string &name, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name linkLocal
         * \brief Starts the proces of creating indentity on backup PEIG.
         * \param linkType type of identity replication
         * \param peigReturnURL URL for application return address.
         * \see AducidPeigLocalLink_t
         * \see aducid_peig_local_link
         *@{
         */
        ADUCID_PUBLIC_FUNC bool linkLocal(AducidPeigLocalLink_t linkType, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool linkLocal(AducidPeigLocalLink_t linkType, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name initPayment
         * \brief FIXME: what does it do?
         * \param usePersonalFactor choise whether operation must be confirmed with
         *        personal factor or not
         * \param peigReturnURL URL for application return address.
         * \see aducid_init_payment
         *@{
         */
        ADUCID_PUBLIC_FUNC bool initPayment(bool usePersonalFactor, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool initPayment(bool usePersonalFactor, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name confirmTextTransaction
         * \brief Starts the transaction for text message confirmation.
         * \param textUTF8 Message for confirmation (must be in UTF8, remember ASCII is ok).
         * \param usePersonalFactor Choise whether operation must be confirmed with
         *        personal factor or not.
         * \param peigReturnURL URL for application return address.
         * \see aducid_confirm_text_transaction
         *@{
         */
        ADUCID_PUBLIC_FUNC bool confirmTextTransaction(const char *textUTF8, bool usePersonalFactor, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool confirmTextTransaction(const string &textUTF8, bool usePersonalFactor, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \name confirmMoneyTransaction
         * \brief Starts the transaction for money transfer.
         * \param fromAccount Account for money withdrawal.
         * \param toAccount Account for money deposit.
         * \param amount ammount of money to be sent.
         * \param usePersonalFactor Choise whether operation must be confirmed with
         *        personal factor or not.
         * \param peigReturnURL URL for application return address.
         * \see aducid_confirm_money_transaction
         *@{
         */
        ADUCID_PUBLIC_FUNC bool confirmMoneyTransaction(const char *fromAccount, const char *toAccount, const char *amount, bool usePersonalFactor, const char *peigReturnURL);
        ADUCID_PUBLIC_FUNC bool confirmMoneyTransaction(const string &fromAccount, const string &toAccount, const string &amount, bool usePersonalFactor, const string &peigReturnURL);
        /**@}*/
        
        /**
         * \brief Closes ADUCID session.
         * \see aducid_close
         *
         * Closes aducid session. You can freely use AducidClient object for another operation.
         */        
        ADUCID_PUBLIC_FUNC bool close();
        
        /**
         * \brief Verifies result of ADUCID operation.
         * \see aducid_verify
         *
         * Verifies previously performed ADUCID operation. ADUCID properties authId,
         * authKey, bindingId and bindingKey must be set before calling this method
         * (at least some of them, depends on binding type).
         */        
        ADUCID_PUBLIC_FUNC bool verify();

        /**
         * \name verifyTransaction
         * \param transactionOutput transaction results
         * \return true if the transaction is completely ok
         * \see aducid_verify_transaction
         *
         * Parameter "transactionOutput" is output parametr. It is filled with transaction details
         * like the message which has been seen by user, digital signature and more.
         *@{
         */
        ADUCID_PUBLIC_FUNC bool verifyTransaction();
        ADUCID_PUBLIC_FUNC bool verifyTransaction(map<string, string> &transactionOutput);
        /**@}*/

        /**
         * \param set PSL set
         * \param useCache if true, result is taken from cache (of course if it is in cache).
         * \return map of attributes
         * \see aducid_get_psl_attributes
         * \see AducidAttributeSet_t
         *
         * Parameter params is output parametr. It is filled with transaction details
         * like the message which has been seen by user, digital signature and more.
         */
        ADUCID_PUBLIC_FUNC map<string, string> getPSLAttributes(AducidAttributeSet_t set, bool useCache);

        /**
         * \param attr one atribute from PSL set ADUCID_ATTRIBUTE_SET_ALL
         * \return string with attribute value (or "" if not found)
         * \see aducid_get_psl_attributes
         * \see getPSLAtributes
         *
         * This method simplifies obtaining one attribute from PSL. It is not very
         * efective if You need more attributes from PSL set. In such case
         * consider use of getPSLAttributes(ADUCID_ATTRIBUTE_SET_ALL).
         */
        ADUCID_PUBLIC_FUNC string getPSLAttribute(const std::string &attr);

        /**
         * \name EPOReadUserAttrSet
         * \brief Read user attribute set from AIM.
         * \param attrSetName name of requested set like "default"
         * \return list of attributes in set
         * \see aducid_epo_read_user_attr_set
         *
         * Attribute set can contain multivalue attribute (for example user can have more
         * email addresses). If it is your case, use Multivalue variant. If you use
         * single value method on multivalue attribute, you will just get one selected
         * value instead of all.
         *
         * Remember that writting single value into multivalue attribute will destroy
         * other values.
         *@{
         */
        ADUCID_PUBLIC_FUNC map<string, string> EPOReadUserAttrSet(const char *attrSetName);
        ADUCID_PUBLIC_FUNC map<string, string> EPOReadUserAttrSet(const string &attrSetName);
        ADUCID_PUBLIC_FUNC map< string, vector<string> > EPOReadUserMultivalueAttrSet(const char *attrSetName);
        ADUCID_PUBLIC_FUNC map< string, vector<string> > EPOReadUserMultivalueAttrSet(const string &attrSetName);
        /**@}*/
        
        /**
         * \name EPOReadUserAttrSet
         * \brief Writes user attribute/s to AIM.
         * \param attrSetName name of requested set like "default"
         * \param attributes list of attributes to be written
         * \see aducid_epo_write_user_attr_set
         *@{
         */
        ADUCID_PUBLIC_FUNC void EPOWriteUserAttrSet(const string &attrSetName, map<string, string>attributes);
        ADUCID_PUBLIC_FUNC void EPOWriteUserAttrSet(const string &attrSetName, map< string, vector<string> >attributes);
        /**@}*/

        /**
         * \brief Method returns userDatabaseIndex.
         * \param handle aducid handle
         * \return user identifier
         */
        ADUCID_PUBLIC_FUNC string userDatabaseIndex();

        /**
         * \brief Returns URL for redirecting into AIMProxy.
         *
         * This function generates a URL which may be used to redirect the user
         * to the AIM-proxy.
         */
        ADUCID_PUBLIC_FUNC string AIMProxyURL() const;
        ADUCID_PUBLIC_FUNC ~AducidClient();
    protected:
        ADUCID_PUBLIC_FUNC map< string, string > AducidListToMap(const AducidAttributeList_t list) const;
        ADUCID_PUBLIC_FUNC map< string, vector<string> > AducidListToMultivalueMap(const AducidAttributeList_t list) const;
        ADUCID_PUBLIC_FUNC AducidAttributeList_t MapToAducidList(const map< string, string > &attrs) const;
        ADUCID_PUBLIC_FUNC AducidAttributeList_t MapToAducidList(const map< string, vector<string> > &attrs) const;
    private:
        AducidHandle_t _handle;
        std::string _AIM;
    };

}
/**@}*/

#endif // __ADUCIDPP_H__
